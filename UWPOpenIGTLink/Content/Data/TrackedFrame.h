/*====================================================================
Copyright(c) 2016 Adam Rankin


Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and / or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
====================================================================*/

#pragma once

// Local includes
#include "TransformName.h"

// IGT includes
#include <igtl_util.h>

// STD includes
#include <array>
#include <map>
#include <memory>

// Windows includes
#include <DirectXMath.h>
#include <collection.h>
#include <dxgiformat.h>

using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation::Numerics;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;

/// An enum to wrap the c define values specified in igtl_util.h
enum IGTLScalarType
{
  IGTL_SCALARTYPE_UNKNOWN = 0,
  IGTL_SCALARTYPE_INT8 = IGTL_SCALAR_INT8,
  IGTL_SCALARTYPE_UINT8 = IGTL_SCALAR_UINT8,
  IGTL_SCALARTYPE_INT16 = IGTL_SCALAR_INT16,
  IGTL_SCALARTYPE_UINT16 = IGTL_SCALAR_UINT16,
  IGTL_SCALARTYPE_INT32 = IGTL_SCALAR_INT32,
  IGTL_SCALARTYPE_UINT32 = IGTL_SCALAR_UINT32,
  IGTL_SCALARTYPE_FLOAT32 = IGTL_SCALAR_FLOAT32,
  IGTL_SCALARTYPE_FLOAT64 = IGTL_SCALAR_FLOAT64,
  IGTL_SCALARTYPE_COMPLEX = IGTL_SCALAR_COMPLEX
};

/// US_IMAGE_TYPE - Defines constant values for ultrasound image type
enum US_IMAGE_TYPE
{
  US_IMG_TYPE_XX,    /*!< undefined */
  US_IMG_BRIGHTNESS, /*!< B-mode image */
  US_IMG_RF_REAL,    /*!< RF-mode image, signal is stored as a series of real values */
  US_IMG_RF_IQ_LINE, /*!< RF-mode image, signal is stored as a series of I and Q samples in a line (I1, Q1, I2, Q2, ...) */
  US_IMG_RF_I_LINE_Q_LINE, /*!< RF-mode image, signal is stored as a series of I samples in a line, then Q samples in the next line (I1, I2, ..., Q1, Q2, ...) */
  US_IMG_RGB_COLOR, /*!< RGB24 color image */
  US_IMG_TYPE_LAST   /*!< just a placeholder for range checking, this must be the last defined image type */
};

/// US_IMAGE_ORIENTATION - Defines constant values for ultrasound image orientation
///   The ultrasound image axes are defined as follows:
///     x axis: points towards the x coordinate increase direction
///     y axis: points towards the y coordinate increase direction
///     z axis: points towards the z coordinate increase direction
///   The image orientation can be defined by specifying which transducer axis corresponds to the x, y and z image axes, respectively.
enum US_IMAGE_ORIENTATION
{
  US_IMG_ORIENT_XX,  /*!< undefined */
  US_IMG_ORIENT_UF, /*!< image x axis = unmarked transducer axis, image y axis = far transducer axis */
  US_IMG_ORIENT_UFD = US_IMG_ORIENT_UF, /*!< image x axis = unmarked transducer axis, image y axis = far transducer axis, image z axis = descending transducer axis */
  US_IMG_ORIENT_UFA, /*!< image x axis = unmarked transducer axis, image y axis = far transducer axis, image z axis = ascending transducer axis */
  US_IMG_ORIENT_UN, /*!< image x axis = unmarked transducer axis, image y axis = near transducer axis */
  US_IMG_ORIENT_UNA = US_IMG_ORIENT_UN, /*!< image x axis = unmarked transducer axis, image y axis = near transducer axis, image z axis = ascending transducer axis */
  US_IMG_ORIENT_UND, /*!< image x axis = unmarked transducer axis, image y axis = near transducer axis, image z axis = descending transducer axis */
  US_IMG_ORIENT_MF, /*!< image x axis = marked transducer axis, image y axis = far transducer axis */
  US_IMG_ORIENT_MFA = US_IMG_ORIENT_MF, /*!< image x axis = marked transducer axis, image y axis = far transducer axis, image z axis = ascending transducer axis */
  US_IMG_ORIENT_MFD, /*!< image x axis = marked transducer axis, image y axis = far transducer axis, image z axis = descending transducer axis */
  US_IMG_ORIENT_AMF,
  US_IMG_ORIENT_MN, /*!< image x axis = marked transducer axis, image y axis = near transducer axis */
  US_IMG_ORIENT_MND = US_IMG_ORIENT_MN, /*!< image x axis = marked transducer axis, image y axis = near transducer axis, image z axis = descending transducer axis */
  US_IMG_ORIENT_MNA, /*!< image x axis = marked transducer axis, image y axis = near transducer axis, image z axis = ascending transducer axis */
  US_IMG_ORIENT_FU, /*!< image x axis = far transducer axis, image y axis = unmarked transducer axis (usually for RF frames)*/
  US_IMG_ORIENT_NU, /*!< image x axis = near transducer axis, image y axis = unmarked transducer axis (usually for RF frames)*/
  US_IMG_ORIENT_FM, /*!< image x axis = far transducer axis, image y axis = marked transducer axis (usually for RF frames)*/
  US_IMG_ORIENT_NM, /*!< image x axis = near transducer axis, image y axis = marked transducer axis (usually for RF frames)*/
  US_IMG_ORIENT_LAST   /*!< just a placeholder for range checking, this must be the last defined orientation item */
};

#ifdef _WIN64
typedef int64 SharedBytePtr;
#else
typedef int32 SharedBytePtr;
#endif

namespace UWPOpenIGTLink
{
  enum TrackedFrameFieldStatus
  {
    FIELD_OK,       /// Field is valid
    FIELD_INVALID   /// Field is invalid
  };

  [Windows::Foundation::Metadata::WebHostHiddenAttribute]
  public ref class TrackedFrame sealed
  {
  private:
    typedef std::map<std::wstring, std::wstring> FieldMapType;

  public:
    property IMapView<Platform::String^, Platform::String^>^ FrameFields {IMapView<Platform::String^, Platform::String^>^ get(); }
    property int32 ImageSizeBytes { int32 get(); void set( int32 arg ); }
    property IVectorView<uint16>^ FrameSize { IVectorView<uint16>^ get(); void set( IVectorView<uint16>^ arg ); }
    property uint16 NumberOfComponents { uint16 get(); void set( uint16 arg ); }
    property IBuffer^ ImageData { IBuffer ^ get(); void set( IBuffer ^ arg ); }
    property SharedBytePtr ImageDataSharedPtr { SharedBytePtr get(); void set( SharedBytePtr arg ); }
    property int32 ScalarType { int32 get(); void set( int32 arg ); }
    property float4x4 EmbeddedImageTransform { float4x4 get(); void set( float4x4 arg ); }
    property uint32 PixelFormat { uint32 get(); void set( uint32 arg ); }
    property uint16 ImageType { uint16 get(); void set( uint16 arg ); }
    property uint16 ImageOrientation { uint16 get(); void set( uint16 arg ); }
    property double Timestamp { double get(); void set( double arg ); }
    property uint16 Width { uint16 get(); }
    property uint16 Height { uint16 get(); }
    property uint16 Depth { uint16 get(); }

  public:
    void SetParameter( Platform::String^ key, Platform::String^ value );
    IMapView<Platform::String^, Platform::String^>^ GetValidTransforms();

    IVectorView<TransformName^>^ TrackedFrame::GetCustomFrameTransformNameList();
    float4x4 GetCustomFrameTransform( TransformName^ transformName );
    Platform::String^ GetCustomFrameField( Platform::String^ fieldName );
    int GetCustomFrameTransformStatus( TransformName^ transformName );

  internal:
    void SetImageData( std::shared_ptr<byte> imageData );
    std::shared_ptr<byte> GetImageData();

    void SetEmbeddedImageTransform( const DirectX::XMFLOAT4X4& matrix );
    const DirectX::XMFLOAT4X4& GetEmbeddedImageTransform();

    void SetCustomFrameField( const std::wstring& fieldName, const std::wstring& value );
    bool GetCustomFrameField( const std::wstring& fieldName, std::wstring& value );

    /// Returns true if the input string ends with "Transform", else false
    static bool IsTransform( const std::wstring& str );

    /// Returns true if the input string ends with "TransformStatus", else false
    static bool IsTransformStatus( const std::wstring& str );

    /*! Convert from field status string to field status enum */
    static TrackedFrameFieldStatus ConvertFieldStatusFromString( const std::wstring& statusStr );

    /*! Convert from field status enum to field status string */
    static std::wstring ConvertFieldStatusToString( TrackedFrameFieldStatus status );

  protected private:
    // Tracking/other related fields
    FieldMapType m_frameFields;

    // Image related fields
    double                    m_timestamp;
    std::shared_ptr<byte>     m_imageData;
    std::array<uint16, 3>     m_frameSize;
    uint16                    m_numberOfComponents;
    int32                     m_frameSizeBytes;
    US_IMAGE_TYPE             m_imageType;
    US_IMAGE_ORIENTATION      m_imageOrientation;
    IGTLScalarType            m_scalarType;
    DirectX::XMFLOAT4X4       m_embeddedImageTransform;
  };
}