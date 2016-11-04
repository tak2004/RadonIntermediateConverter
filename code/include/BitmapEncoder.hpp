#ifndef IP_ENCODER_BITMAPENCODER_HPP
#define IP_ENCODER_BITMAPENCODER_HPP

#include <RadonFramework/IO/Encoders/ImageEncoder.hpp>

namespace ImageProcessor { namespace Encoder {

class BitmapEncoder:public RF_Encoders::ImageEncoder
{
public:
    BitmapEncoder();

    static const RF_Type::UInt32 FOURCC = '  MB';

    static RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC);
    static RF_Type::Bool IsInterfaceSupported(const RF_Type::UInt32 FourCC,
                                              RF_Encoders::Interface Target);

    virtual void SetLayers(RF_Type::UInt32 NewLayerCount) override;
    virtual RF_Type::Bool StoreLayerData(RF_Type::UInt32 Layer,
        const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data) override;
    
    virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> GenerateData() override;
protected:
    RF_Collect::Array<RF_Mem::AutoPointerArray<RF_Type::UInt8> > m_Layer;
};

} }

#ifndef IP_SHORTHAND_NAMESPACE_ENCODER
#define IP_SHORTHAND_NAMESPACE_ENCODER
namespace IP_Encoder = ImageProcessor::Encoder;
#endif

#endif // IP_ENCODER_BITMAPENCODER_HPP