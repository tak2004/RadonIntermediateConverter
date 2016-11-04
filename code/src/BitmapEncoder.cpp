#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Radon.hpp>
#include "BitmapEncoder.hpp"

#include "BitmapStructure.hpp"

namespace ImageProcessor { namespace Encoder {

RF_Type::Bool BitmapEncoder::StoreLayerData(RF_Type::UInt32 Layer,
    const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    if(Layer < m_Layers)
    {
        m_Layer(Layer) = Data;
    }
    return false;
}

RF_Type::Bool BitmapEncoder::IsFourCCSupported(const RF_Type::UInt32 FourCC)
{
    return (FourCC &0xffff) == 'MB';
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> BitmapEncoder::GenerateData()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;

    RF_Type::Size bytes = (m_PixelFormat.BitPerPixel * m_Width * m_Height * m_Layers) >> 3;
    bytes += sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    result = RF_Mem::AutoPointerArray<RF_Type::UInt8>(new RF_Type::UInt8[bytes], bytes);
    BITMAPFILEHEADER* fileHeader = reinterpret_cast<BITMAPFILEHEADER*>(result.Get());
    BITMAPINFOHEADER* infoHeader = reinterpret_cast<BITMAPINFOHEADER*>(fileHeader + 1);

    infoHeader->biSize = sizeof(BITMAPINFOHEADER);
    infoHeader->biSizeImage =( m_PixelFormat.BitPerPixel * m_Width * m_Height * m_Layers) >> 3;
    infoHeader->biWidth = m_Width;
    infoHeader->biHeight = m_Height;
    infoHeader->biPlanes = 1;
    infoHeader->biBitCount = m_PixelFormat.BitPerPixel;
    infoHeader->biCompression = 0;
    infoHeader->biXPelsPerMeter = 0;
    infoHeader->biYPelsPerMeter = 0;
    infoHeader->biClrUsed = 0;
    infoHeader->biClrImportant = 0;

    fileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + infoHeader->biSize;
    fileHeader->bfSize = bytes;
    fileHeader->bfType = 'B' + ('M' << 8);    

    RF_Type::UInt8* bitmapData = reinterpret_cast<RF_Type::UInt8*>(infoHeader + 1);
    for(RF_Type::Size i = 0; i < m_Layers; ++i)
    {
        for(RF_Type::Size p = 0; p < m_Width*m_Height; ++p)
        {
            bitmapData[p * 3] = m_Layer(i).Get()[(p * 3) + 2];
            bitmapData[(p * 3)+1] = m_Layer(i).Get()[(p * 3) + 1];
            bitmapData[(p * 3)+2] = m_Layer(i).Get()[p * 3 ];
        }
        //RF_SysMem::Copy(bitmapData, m_Layer(i).Get(), m_Layer(i).Size());
        bitmapData += m_Layer(i).Size();
    }

    return result;
}

RF_Type::Bool BitmapEncoder::IsInterfaceSupported(const RF_Type::UInt32 FourCC, 
                                                  RF_Encoders::Interface Target)
{
    return IsFourCCSupported(FourCC) && (Target == RF_Encoders::Interface::Image ||
                                         Target == RF_Encoders::Interface::Generic);
}

BitmapEncoder::BitmapEncoder()
:ImageEncoder()
{

}

void BitmapEncoder::SetLayers(RF_Type::UInt32 NewLayerCount)
{
    ImageEncoder::SetLayers(NewLayerCount);
    m_Layer.Resize(m_Layers);
}

} }