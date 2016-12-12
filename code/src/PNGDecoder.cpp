#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Radon.hpp>
#include "PNGDecoder.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace RadonIntermediateConverter {

RF_Mem::AutoPointerArray<RF_Type::UInt8> PNGDecoder::LoadLayer(RF_Type::UInt32 Layer)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if((m_PixelFormat.BitPerPixel >= 24) && Layer == 0)
    {
        int width, height, comp, req = 3;
        stbi_uc* imageData = stbi_load_from_memory(m_ByteData, m_Bytes, &width, &height, &comp, req);
        m_ImageData = RF_Mem::AutoPointerArray<RF_Type::UInt8>(imageData, width*height*comp);
        result = m_ImageData.Clone();
    }

    return result;
}

RF_Type::Size PNGDecoder::LoadInformation()
{
    int width, height, comps;
    if (stbi_info_from_memory(m_ByteData, m_Bytes, &width, &height, &comps) == 1)
    {
        m_Width = width;
        m_Height = height;
        m_Layers = 1;
        m_PixelFormat.Type = RF_Draw::PixelType::Unsigned;
        m_PixelFormat.BitPerPixel = 24;
        m_PixelFormat.Channels.Resize(3);
        m_PixelFormat.Channels(0).Bits = 8;
        m_PixelFormat.Channels(0).Type = RF_Draw::ChannelType::Red;
        m_PixelFormat.Channels(1).Bits = 8;
        m_PixelFormat.Channels(1).Type = RF_Draw::ChannelType::Green;
        m_PixelFormat.Channels(2).Bits = 8;
        m_PixelFormat.Channels(2).Type = RF_Draw::ChannelType::Blue;
    }
    return 0;
}

RF_Type::Bool PNGDecoder::Seekable()
{
    return true;
}

RF_Type::Size PNGDecoder::LoadData(void* Data, unsigned int Buffersize)
{
    return 0;
}

RF_Type::Size PNGDecoder::SeekData(RF_Type::Size Bytes)
{
    RF_Type::Size result = RF_Math::Integer<RF_Type::Size>::Min(Bytes, m_Bytes - (m_Pointer + Bytes + m_DataOffset));
    m_Pointer += result;
    return result;
}

RF_Type::Size PNGDecoder::TotalData()
{
    return m_Bytes - m_DataOffset;
}

RF_Type::Size PNGDecoder::TellData()
{
    return m_Pointer;
}

RF_Type::Bool PNGDecoder::IsFourCCSupported(const RF_Type::UInt32 FourCC)
{
    return FourCC == 0x474e5089;
}

void PNGDecoder::SetData(RF_Type::UInt8* ByteData, RF_Type::Size Bytes)
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

RF_Type::Bool PNGDecoder::IsInterfaceSupported(const RF_Type::UInt32 FourCC, 
                                                  RF_Decoders::Interface Target)
{
    return IsFourCCSupported(FourCC) && (Target == RF_Decoders::Interface::Image ||
                                         Target == RF_Decoders::Interface::Generic);
}

PNGDecoder::PNGDecoder()
:ImageDecoder()
,m_ByteData(0)
,m_Bytes(0)
,m_Pointer(0)
,m_DataOffset(0)
{

}

}