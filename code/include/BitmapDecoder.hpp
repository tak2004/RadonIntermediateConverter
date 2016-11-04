#ifndef IP_DECODER_BITMAPDECODER_HPP
#define IP_DECODER_BITMAPDECODER_HPP

#include <RadonFramework/IO/Decoders/ImageDecoder.hpp>

namespace ImageProcessor { namespace Decoder {

class BitmapDecoder:public RF_Decoders::ImageDecoder
{
public:
    BitmapDecoder();

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
};

} }

#ifndef IP_SHORTHAND_NAMESPACE_DECODER
#define IP_SHORTHAND_NAMESPACE_DECODER
namespace IP_Decoder = ImageProcessor::Decoder;
#endif

#endif // IP_DECODER_BITMAPDECODER_HPP