/**
 * @file AnsiIsoInterface.h
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <iengine_ansi_iso.h>

/**
 * @brief AnsiIsoInterface
 *
 * Defines AnsiIso native interface.
 *
 */
template<class DerivedInterface>
class AnsiIsoInterface
{
  int IEngine_Init() { static_cast<DerivedInterface*>(this)->IEngine_Init(); }

  int IEngine_Terminate()
  {
    static_cast<DerivedInterface*>(this)->IEngine_Terminate();
  }

  const char* IEngine_GetVersionString()
  {
    static_cast<DerivedInterface*>(this)->IEngine_GetVersionString();
  }

  int IEngine_GetHwidByMethod(IENGINE_HWID_METHOD method,
                              char* hwid,
                              int* length)
  {
    static_cast<DerivedInterface*>(this)->IIEngine_GetHwidByMethod(
      method, hwid, length);
  }

  // char * IEngine_GetErrorMessage( int errcode );
  // int IEngine_SetDebugLevel(int debugLevel);
  // int ANSI_ConvertToISO(const BYTE *ansiTemplate,int *length,BYTE
  // *isoTemplate); int ISO_ConvertToANSI(const BYTE *isoTemplate,int
  // *length,BYTE *ansiTemplate); int ISO_ConvertToISOCardCC(const BYTE
  // *isoTemplate,int maximumMinutiaeCount, IENGINE_SORT_ORDER minutiaeOrder,
  // IENGINE_SORT_ORDER minutiaeSecondaryOrder, int *length,BYTE
  // *isoCCTemplate); int ISO_CARD_CC_ConvertToISO(const BYTE *isoCCTemplate,int
  // *length,BYTE *isoTemplate);
  // int IEngine_GetImageQuality( int width, int height, const BYTE *rawImage,
  // int *quality ); int IEngine_LoadBMP(const char *filename,int *width, int
  // *height,BYTE *rawImage, int *length); int IEngine_MakeBMP(int width, int
  // height,const BYTE *rawImage, BYTE *bmpImageData, int *length); int
  // IEngine_ConvertBMP(const BYTE *bmpImage,int *width, int *height,BYTE
  // *rawImage, int *length); int IEngine_ConvertToRaw(const BYTE *imageData,
  // int imageLength, IENGINE_IMAGE_FORMAT imageFormat, int *width, int
  // *height,BYTE *rawImage, int *rawImageLength); int
  // IEngine_ConvertRawToImage(const BYTE *rawImage, int width, int height,BYTE
  // *outImage, IENGINE_IMAGE_FORMAT imageFormat, int rate, int *length); int
  // IEngine_ResizeImage(int width, int height, const BYTE *rawImage, int dpi,
  // int *outWidth, int *outHeight, BYTE *outImage); int
  // IEngine_ResizeImageInPlace(int width, int height, BYTE *rawImage, int dpi,
  // int *outWidth, int *outHeight); int IEngine_ConvertRawToIso19794_4(const
  // unsigned char *rawImage,int width,int height,unsigned char fingerPosition,
  // unsigned char imageFormat, unsigned int dpiX,unsigned int dpiY, unsigned
  // char *outData,int rate,int *length); int
  // IEngine_ConvertIso19794_4ToRaw(const unsigned char *isoFingerImage,unsigned
  // int isoImageLength,int *width,int *height,unsigned char *fingerPosition,
  // unsigned char *imageFormat, unsigned int *dpiX,unsigned int *dpiY, unsigned
  // char *rawImage,int *rawImageLength); int ANSI_CreateTemplate(int width, int
  // height, const BYTE *rawImage, BYTE * ansiTemplate); int
  // ANSI_CreateTemplate2(int width, int height, const BYTE *rawImage, int dpi,
  // BYTE * ansiTemplate); int ANSI_CreateTemplateEx(int width, int height,
  // const BYTE *rawImage, BYTE * ansiTemplate, const char *skeletonImageFile,
  // const char *binarizedImageFile, const char *minutiaeImageFile); int
  // ANSI_VerifyMatch(const BYTE *probeTemplate, const BYTE *galleryTemplate,
  // int maxRotation, int *score); int ANSI_VerifyMatchEx(const BYTE
  // *probeTemplate, int probeView, const BYTE *galleryTemplate, int
  // galleryView, int maxRotation, int *score); int ISO_CreateTemplate(int
  // width, int height, const BYTE *rawImage, BYTE * isoTemplate); int
  // ISO_CreateTemplate2(int width, int height, const BYTE *rawImage, int dpi,
  // BYTE * isoTemplate); int ISO_CreateTemplateEx(int width, int height, const
  // BYTE *rawImage, BYTE * isoTemplate, const char *skeletonImageFile, const
  // char *binarizedImageFile, const char *minutiaeImageFile); int
  // ISO_CreateTemplateEx2(int width, int height, const BYTE *rawImage, BYTE *
  // isoTemplate, BYTE *filteredImage, BYTE *binarizedImage, BYTE
  // *skeletonImage, int *blockWidth, int *blockHeight, BYTE * bMask, BYTE
  // *bOrientation, BYTE * bQuality); int ISO_CreateTemplateInPlace(int
  // width,int height,int dpi,BYTE *rawImageBuffer,int *rawImageBufferLength,
  // BYTE *workBuffer,int *workBufferLength, BYTE *isoTemplate); // On embedded
  // systems only int ISO_VerifyMatch(const BYTE *probeTemplate, const BYTE
  // *galleryTemplate, int maxRotation, int *score); int ISO_VerifyMatchEx(const
  // BYTE *probeTemplate, int probeView, const BYTE *galleryTemplate, int
  // galleryView, int maxRotation, int *score); int ISO_VerifyMatchEx2(const
  // BYTE *probeTemplate, int probeView, const BYTE *galleryTemplate, int
  // galleryView, int maxRotation, int *score,int*dx,int *dy,int *rotation,int
  // *associationCount,BYTE *assocProbeMinutiae,BYTE *assocGalleryMinutiae,BYTE
  // *assocQuality);
  // int ANSI_GetTemplateParameter(const BYTE *ansiTemplate,
  // IENGINE_TEMPLATE_PARAMETER parameter, int *value);
  // int ANSI_SetTemplateParameter(BYTE *ansiTemplate,
  // IENGINE_TEMPLATE_PARAMETER parameter, int value); int
  // ANSI_GetFingerView(const BYTE *ansiTemplate,int fingerView,BYTE
  // *outTemplate); int ANSI_DrawMinutiae(const BYTE *ansiTemplate,int width,int
  // height, unsigned char *inputImage, unsigned char *outputBmpImage,int
  // *outputImageLength); int ANSI_GetMinutiae(const BYTE *ansiTemplate,
  // IENGINE_MINUTIAE minutiae[256], int *minutiaeCount); int
  // ANSI_MergeTemplates(const BYTE *referenceTemplate,const BYTE
  // *addedTemplate,int *length,BYTE *outTemplate); int ANSI_LoadTemplate(const
  // char *filename, BYTE *ansiTemplate); int ANSI_RemoveMinutiae(const BYTE
  // *inTemplate, int maximumMinutiaeCount, int *length, BYTE *outTemplate); int
  // ANSI_SaveTemplate(const char *filename, const BYTE *ansiTemplate); int
  // ISO_GetTemplateParameter(const BYTE *isoTemplate,
  // IENGINE_TEMPLATE_PARAMETER parameter, int *value); int
  // ISO_SetTemplateParameter(BYTE *isoTemplate, IENGINE_TEMPLATE_PARAMETER
  // parameter, int value); int ISO_GetFingerView(const BYTE *isoTemplate,int
  // fingerView,BYTE *outTemplate); int ISO_DrawMinutiae(const BYTE
  // *isoTemplate,int width,int height, unsigned char *inputImage, unsigned char
  // *outputBmpImage,int *outputImageLength); int ISO_GetMinutiae(const BYTE
  // *isoTemplate, IENGINE_MINUTIAE minutiae[256], int *minutiaeCount); int
  // ISO_MergeTemplates(const BYTE *referenceTemplate,const BYTE
  // *addedTemplate,int *length,BYTE *outTemplate); int ISO_LoadTemplate(const
  // char *filename, BYTE *isoTemplate); int ISO_RemoveMinutiae(const BYTE
  // *inTemplate, int maximumMinutiaeCount, int *length, BYTE *outTemplate); int
  // ISO_SaveTemplate(const char *filename, const BYTE *isoTemplate); int
  // IEngine_ConvertTemplate(IENGINE_TEMPLATE_FORMAT inputTemplateType, const
  // BYTE *inputTemplate, IENGINE_TEMPLATE_FORMAT outputTemplateType, int
  // *length, BYTE *outputTemplate); int ISO_CARD_CC_GetMinutiaeData(const BYTE
  // *isoCCTemplate, int *minutiaeCount, BYTE *minutiaeData, int
  // *minutiaeDataSize);
};
