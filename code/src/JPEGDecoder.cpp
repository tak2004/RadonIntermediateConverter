#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Radon.hpp>
#include "JPEGDecoder.hpp"

#include "jpgd.h"

namespace ImageProcessor { namespace Decoder {

RF_Mem::AutoPointerArray<RF_Type::UInt8> JPEGDecoder::LoadLayer(RF_Type::UInt32 Layer)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if(LoadInformation() && (m_PixelFormat.BitPerPixel >= 24) && Layer == 0)
    {
        result = m_ImageData.Clone();
    }

    return result;
}

RF_Type::Size JPEGDecoder::LoadInformation()
{
    int width, height, comps, req=3;
    unsigned char* result = jpgd::decompress_jpeg_image_from_memory(m_ByteData, m_Bytes, &width, &height, &comps, req);
    m_ImageData = RF_Mem::AutoPointerArray<RF_Type::UInt8>(result, width*height*comps);
    m_Width = width;
    m_Height = height;
    m_Layers = 1;
    m_PixelFormat.BitPerPixel = 24;
    m_PixelFormat.Channels = 3;
    return m_ImageData.Size();
}

RF_Type::Bool JPEGDecoder::Seekable()
{
    return true;
}

RF_Type::Size JPEGDecoder::LoadData(void* Data, unsigned int Buffersize)
{

    return 0;
}

RF_Type::Size JPEGDecoder::SeekData(RF_Type::Size Bytes)
{
    RF_Type::Size result = RF_Math::Integer<RF_Type::Size>::ClampLowerBound(Bytes, m_Bytes - (m_Pointer + Bytes + m_DataOffset));
    m_Pointer += result;
    return result;
}

RF_Type::Size JPEGDecoder::TotalData()
{
    return m_Bytes - m_DataOffset;
}

RF_Type::Size JPEGDecoder::TellData()
{
    return m_Pointer;
}

RF_Type::Bool JPEGDecoder::IsFourCCSupported(const RF_Type::UInt32 FourCC)
{
    return (FourCC &0xffff) == 0xd8ff;
}

void JPEGDecoder::SetData(RF_Type::UInt8* ByteData, RF_Type::Size Bytes)
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

RF_Type::Bool JPEGDecoder::IsInterfaceSupported(const RF_Type::UInt32 FourCC, 
                                                  RF_Decoders::Interface Target)
{
    return IsFourCCSupported(FourCC) && (Target == RF_Decoders::Interface::Image ||
                                         Target == RF_Decoders::Interface::Generic);
}

JPEGDecoder::JPEGDecoder()
:ImageDecoder()
,m_ByteData(0)
,m_Bytes(0)
,m_Pointer(0)
,m_DataOffset(0)
{

}

} }