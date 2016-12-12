#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Radon.hpp>
#include "PNGEncoder.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace RadonIntermediateConverter {

RF_Type::Bool PNGEncoder::StoreLayerData(RF_Type::UInt32 Layer,
    const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    if(Layer < m_Layers)
    {
        m_Layer(Layer) = Data;
    }
    return false;
}

RF_Type::Bool PNGEncoder::IsFourCCSupported(const RF_Type::UInt32 FourCC)
{
    return FourCC == FOURCC;
}

void writePNGCallback(void *context, void *data, int size)
{
    auto* buffer = reinterpret_cast<RF_Mem::AutoPointerArray<RF_Type::UInt8>*>(context);
    buffer->New(size);
    RF_SysMem::Copy(buffer->Get(), data, size);
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> PNGEncoder::GenerateData()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;

    RF_Type::Size bytes = (m_PixelFormat.BitPerPixel * m_Width * m_Height * m_Layers) >> 3;
    stbi_write_png_to_func(writePNGCallback, &result, m_Width, m_Height, m_PixelFormat.Channels.Count(), m_Layer(0).Get(),0);
    return result;
}

RF_Type::Bool PNGEncoder::IsInterfaceSupported(const RF_Type::UInt32 FourCC, 
                                                  RF_Encoders::Interface Target)
{
    return IsFourCCSupported(FourCC) && (Target == RF_Encoders::Interface::Image ||
                                         Target == RF_Encoders::Interface::Generic);
}

PNGEncoder::PNGEncoder()
:ImageEncoder()
{

}

void PNGEncoder::SetLayers(RF_Type::UInt32 NewLayerCount)
{
    ImageEncoder::SetLayers(NewLayerCount);
    m_Layer.Resize(m_Layers);
}

const RF_Type::UInt32 PNGEncoder::FOURCC = 0x474e5089;

}