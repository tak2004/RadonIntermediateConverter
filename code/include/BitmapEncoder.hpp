#ifndef RIC_BITMAPENCODER_HPP
#define RIC_BITMAPENCODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Encoders/ImageEncoder.hpp>

namespace RadonIntermediateConverter {

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

} 

#ifndef RIC_SHORTHAND_NAMESPACE
#define RIC_SHORTHAND_NAMESPACE
namespace RIC = RadonIntermediateConverter;
#endif

#endif // RIC_BITMAPENCODER_HPP