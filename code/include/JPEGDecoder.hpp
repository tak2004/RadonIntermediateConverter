#ifndef RIC_JPEGDECODER_HPP
#define RIC_JPEGDECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Decoders/ImageDecoder.hpp>

namespace RadonIntermediateConverter {

class JPEGDecoder:public RF_Decoders::ImageDecoder
{
public:
    JPEGDecoder();

    static RF_Type::Bool IsFourCCSupported(const RF_Type::UInt32 FourCC);
    static RF_Type::Bool IsInterfaceSupported(const RF_Type::UInt32 FourCC,
                                              RF_Decoders::Interface Target);

    virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> LoadLayer(RF_Type::UInt32 Layer) override;

    virtual RF_Type::Size LoadInformation() override;
    virtual RF_Type::Bool Seekable() override;
    virtual RF_Type::Size LoadData(void* Data, unsigned int Buffersize) override;
    virtual RF_Type::Size SeekData(RF_Type::Size Bytes) override;
    virtual RF_Type::Size TotalData() override;
    virtual RF_Type::Size TellData() override;
    virtual void SetData(RF_Type::UInt8* ByteData, RF_Type::Size Bytes) override;
protected:
    RF_Type::UInt8* m_ByteData;
    RF_Type::Size m_Bytes;
    RF_Type::Size m_Pointer;
    RF_Type::Size m_DataOffset;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_ImageData;
};

}

#ifndef RIC_SHORTHAND_NAMESPACE
#define RIC_SHORTHAND_NAMESPACE
namespace RIC = RadonIntermediateConverter;
#endif

#endif // RIC_JPEGDECODER_HPP