#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Radon.hpp>
#include "BitmapDecoder.hpp"

#include "BitmapStructure.hpp"

namespace ImageProcessor { namespace Decoder {

RF_Mem::AutoPointerArray<RF_Type::UInt8> BitmapDecoder::LoadLayer(RF_Type::UInt32 Layer)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if(LoadInformation() && (m_PixelFormat.BitPerPixel >= 24) && Layer == 0)
    {
        RF_Type::UInt8* data = m_ByteData+m_DataOffset+m_Pointer;
        result = RF_Mem::AutoPointerArray<RF_Type::UInt8>(new RF_Type::UInt8[TotalData()],TotalData());
        RF_SysMem::Copy(result.Get(), data, TotalData());
    }

    return result;
}

RF_Type::Size BitmapDecoder::LoadInformation()
{
    BITMAPFILEHEADER* bmpheader;
    BITMAPINFOHEADER* bmpinfo;
    RF_Type::Size bytesread = 0;
    if(m_Bytes >= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))
    {
        bytesread = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bmpheader = reinterpret_cast<BITMAPFILEHEADER*>(m_ByteData);
        bmpinfo = reinterpret_cast<BITMAPINFOHEADER*>(bmpheader + 1);
        m_Pointer = 0;
        m_DataOffset = bmpheader->bfOffBits;
        m_Width = bmpinfo->biWidth;
        m_Height = bmpinfo->biHeight;
        m_Layers = 1;

        m_PixelFormat.BitPerPixel = bmpinfo->biBitCount;

        m_PixelFormat.Channels.Resize(3);
        m_PixelFormat.Channels(0).Type = RF_Draw::ChannelType::Red;
        m_PixelFormat.Channels(1).Type = RF_Draw::ChannelType::Green;
        m_PixelFormat.Channels(2).Type = RF_Draw::ChannelType::Blue;
        m_PixelFormat.Channels(0).Bits = 8;
        m_PixelFormat.Channels(1).Bits = 8;
        m_PixelFormat.Channels(2).Bits = 8;

        if(bmpinfo->biBitCount == 32)
        {
            m_PixelFormat.Channels.Resize(4);
            m_PixelFormat.Channels(3).Type = RF_Draw::ChannelType::Alpha;
            m_PixelFormat.Channels(3).Bits = 8;
        }
    }
    return bytesread;
}

RF_Type::Bool BitmapDecoder::Seekable()
{
    return true;
}

RF_Type::Size BitmapDecoder::LoadData(void* Data, unsigned int Buffersize)
{

    return 0;
}

RF_Type::Size BitmapDecoder::SeekData(RF_Type::Size Bytes)
{
    RF_Type::Size result = RF_Math::Integer<RF_Type::Size>::ClampLowerBound(Bytes, m_Bytes - (m_Pointer + Bytes + m_DataOffset));
    m_Pointer += result;
    return result;
}

RF_Type::Size BitmapDecoder::TotalData()
{
    return m_Bytes - m_DataOffset;
}

RF_Type::Size BitmapDecoder::TellData()
{
    return m_Pointer;
}

RF_Type::Bool BitmapDecoder::IsFourCCSupported(const RF_Type::UInt32 FourCC)
{
    return (FourCC &0xffff) == 'MB';
}

void BitmapDecoder::SetData(RF_Type::UInt8* ByteData, RF_Type::Size Bytes)
{
    m_DataOffset = 0;
    m_ByteData = 0;
    m_Bytes = 0;
    if(ByteData != 0 && Bytes > 0)
    {
        m_ByteData = ByteData;
        m_Bytes = Bytes;
    }
}

RF_Type::Bool BitmapDecoder::IsInterfaceSupported(const RF_Type::UInt32 FourCC, 
                                                  RF_Decoders::Interface Target)
{
    return IsFourCCSupported(FourCC) && (Target == RF_Decoders::Interface::Image ||
                                         Target == RF_Decoders::Interface::Generic);
}

BitmapDecoder::BitmapDecoder()
:ImageDecoder()
,m_ByteData(0)
,m_Bytes(0)
,m_Pointer(0)
,m_DataOffset(0)
{

}

} }