#include "IntermediateFormats.hpp"
#include "RadonFramework/Radon.hpp"
#include "BitmapDecoder.hpp"
#include "BitmapEncoder.hpp"
#include "JPEGDecoder.hpp"
#include "PNGDecoder.hpp"
#include "PNGEncoder.hpp"

namespace RadonIntermediateConverter {

void RegisterFormats()
{
    RF_Mem::AutoPointer<RF_IO::DecoderService> bitmapDecoder(new RF_IO::GenericDecoderService<BitmapDecoder>("Bitmap Decoder"_rfs));
    RF_IO::DecoderServiceLocator::Register(bitmapDecoder);

    RF_Mem::AutoPointer<RF_IO::EncoderService> bitmapEncoder(new RF_IO::GenericEncoderService<BitmapEncoder>("Bitmap Encoder"_rfs));
    RF_IO::EncoderServiceLocator::Register(bitmapEncoder);

    RF_Mem::AutoPointer<RF_IO::DecoderService> jpegDecoder(new RF_IO::GenericDecoderService<JPEGDecoder>("JPEG Decoder"_rfs));
    RF_IO::DecoderServiceLocator::Register(jpegDecoder);

    RF_Mem::AutoPointer<RF_IO::DecoderService> pngDecoder(new RF_IO::GenericDecoderService<PNGDecoder>("PNG Decoder"_rfs));
    RF_IO::DecoderServiceLocator::Register(pngDecoder);

    RF_Mem::AutoPointer<RF_IO::EncoderService> pngEncoder(new RF_IO::GenericEncoderService<PNGEncoder>("PNG Encoder"_rfs));
    RF_IO::EncoderServiceLocator::Register(pngEncoder);
}

}