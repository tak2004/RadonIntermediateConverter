#ifndef RIC_INTERMEDIATEFORMATS_HPP
#define RIC_INTERMEDIATEFORMATS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonIntermediateConverter {

void RegisterFormats();

}

#ifndef RIC_SHORTHAND_NAMESPACE
#define RIC_SHORTHAND_NAMESPACE
namespace RIC = RadonIntermediateConverter;
#endif

#endif // !RIC_INTERMEDIATEFORMATS_HPP