#include "IntermediateFormats.hpp"
#include "RadonFramework/Radon.hpp"

namespace RadonIntermediateConverter {

void RegisterFormats()
{
    RF_Mem::AutoPointer<DecoderService> bitmapDecoder(new GenericDecoderService<IP_Decoder::BitmapDecoder>("Bitmap Decoder"));
    RF_IO::DecoderServiceLocator::Register(bitmapDecoder);

    RF_Mem::AutoPointer<EncoderService> bitmapEncoder(new GenericEncoderService<IP_Encoder::BitmapEncoder>("Bitmap Encoder"));
    RF_IO::EncoderServiceLocator::Register(bitmapEncoder);

    RF_Mem::AutoPointer<DecoderService> jpegDecoder(new GenericDecoderService<IP_Decoder::JPEGDecoder>("JPEG Decoder"));
    RF_IO::DecoderServiceLocator::Register(jpegDecoder);
}

}