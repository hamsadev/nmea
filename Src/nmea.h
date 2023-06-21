/**
 * @file nmea.h
 * @author Hamid Salehi (hamsame.dev@gmail.com)
 * @brief nmea lib header file
 * @version 0.2
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2022 Hamid Salehi
 *
 * MIT License
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  ZAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#ifndef _NMEA_H_
#define _NMEA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "Param.h"


#define NMEA_MESSAGE_MAX_LENGTH             255
#define NMEA_FIELD_MAX_LENGTH               20

#define NMEA_MESSAGE_TALKER_LENGTH          2
#define NMEA_MESSAGE_TYPE_LENGTH            3
#define NMEA_MESSAGE_ID_LENGTH              NMEA_MESSAGE_TALKER_LENGTH + NMEA_MESSAGE_TYPE_LENGTH

#define NMEA_DEBUG                          1


typedef enum {
    TALKER_GP,  // Global Positioning System (GPS)
    TALKER_GL,  // Global Navigation Satellite System (GLONASS)
    TALKER_GN,  // Multiple Global Navigation Satellite Systems (e.g., GPS and GLONASS)
    TALKER_GA,  // Galileo - European Global Navigation Satellite System
    TALKER_GB,  // BeiDou - Chinese Satellite Navigation System
    TALKER_SB,  // Other Satellite-Based Positioning System (non-standard)
    TALKER_II,  // Internal Inland Navigation System
    TALKER_IN,  // Indian Regional Navigation Satellite System
    TALKER_EX,  // European Marine-based Navigation System
    TALEKR_NUM,
} NMEA_talkerType;

/************************************************************************/
/*  DATAS SEGMENTS TYPEDEFS                                 */
/************************************************************************/
typedef enum
{
    GGA_MessageID       = 0, // Message ID
    GGA_UTCTime         = 1, // Time in format 'hhmmss.sss'
    GGA_latitude        = 2, // Latitude in format 'ddmm.mmmm' (degrees and minutes)
    GGA_northSouth      = 3, // 'N' = North | 'S' = South
    GGA_Longitude       = 4, // Longitude in format 'ddmm.mmmm' (degrees and minutes)
    GGA_eastWest        = 5, // 'E' = East | 'W' = West
    GGA_fixStatus       = 6, // '0' = Invalid
                             // '1' = GNSS fix
                             // '2' = DGPS fix
                             // '6' = Estimated (dead reckoning) Mode
    GGA_SVNum           = 7, // Number of satellites being used (0~24)
    GGA_HDOP            = 8, // Horizontal dilution of precision
    GGA_atitude         = 9, // Altitude in meters according to WGS84 ellipsoid
    GGA_atitudeUnit     = 10,
    GGA_geoidSeparation = 11, // Height of geoid (means sea level) above WGS84 ellipsoid, meter
    GGA_geoidSeparationUnit =12,
    GGA_DGPS_Age        = 13, // Age of DGPS data in seconds, empty if DGPS is not used
    GGA_DGPS_StationID  = 14, // DGPS station ID, empty if DGPS is not used
    GGA_checksum        = 15, // Checksum
    GGA_fieldNum,

}GGA_field;

typedef enum GLLag
{
    GLL_MessageID       = 0, // Message ID
    GLL_latitude        = 1, // Latitude in format 'ddmm.mmmm' (degrees and minutes)
    GLL_northSouth      = 2, // 'N' = North | 'S' = South
    GLL_Longitude       = 3, // Longitude in format 'ddmm.mmmm' (degrees and minutes)
    GLL_eastWest        = 4, // 'E' = East | 'W' = West
    GLL_UTCTime         = 5, // Time in format „hhmmss.sss‟
    GLL_dataValid       = 6, //'V'=Invalid | 'A'=Valid
    GLL_positioningMode = 7, //'N'=No fix | 'A'=Autonomous GNSS fix | D‟=Differential GNSS fix
    GLL_checksum        = 8, // Checksum
    GLL_fieldNum,

}GLL_field;

typedef enum
{
    GSA_MessageID       = 0, // Message ID
    GSA_mode            = 1, // Auto selection of 2D or 3D fix
                             // 'M'=Manual, forced to switch 2D/3D mode
                             // 'A'=Allowed to automatically switch 2D/3D mode
    GSA_fixStatus       = 2, // '1'=No fix
                             // '2'=2D fix
                             // '3'=3D fix
    GSA_satelliteUsed_1 = 3, // Satellite used on channel 1
    GSA_satelliteUsed_2 = 4, // Satellite used on channel 2
    GSA_satelliteUsed_3 = 5, // Satellite used on channel 3
    GSA_satelliteUsed_4 = 6, // Satellite used on channel 4
    GSA_satelliteUsed_5 = 7, // Satellite used on channel 5
    GSA_satelliteUsed_6 = 8, // Satellite used on channel 6
    GSA_satelliteUsed_7 = 9, // Satellite used on channel 7
    GSA_satelliteUsed_8 = 10, // Satellite used on channel 8
    GSA_satelliteUsed_9 = 11, // Satellite used on channel 9
    GSA_satelliteUsed_10 = 12, // Satellite used on channel 10
    GSA_satelliteUsed_11 = 13, // Satellite used on channel 11
    GSA_satelliteUsed_12 = 14, // Satellite used on channel 12
    GSA_PDOP            = 15, // Position dilution of precision
    GSA_HDOP            = 16, // Horizontal dilution of precision
    GSA_VDOP            = 17, // Vertical dilution of precision
    GSA_checksum        = 18, // Checksum
    GSA_fieldNum,

}GSA_field;

typedef enum
{
    GSV_MessageID       = 0, // Message ID
    GSV_messageNumber   = 1, // Number of messagees, total number of GPGSV messages begin output (1~4)
    GSV_sequenceNumber  = 2, // Sequence number of this entry (1~4)
    GSV_satellitesView  = 3, // Total satellites in view
    GSV_satelliteID_1   = 4, // Satellite ID
    GSV_elevation_1     = 5, // Elevation in degree (1~90)
    GSV_azimuth_1       = 6, // Azimuth in degree (0~359)
    GSV_SNR_1           = 7, // Signal to noise ration in dB-Hz (0~99), empty if not tracking
    GSV_satelliteID_2   = 8, // Satellite ID
    GSV_elevation_2     = 9, // Elevation in degree (1~90)
    GSV_azimuth_2       = 10, // Azimuth in degree (0~359)
    GSV_SNR_2           = 11, // Signal to noise ration in dB-Hz (0~99), empty if not tracking
    GSV_satelliteID_3   = 12, // Satellite ID
    GSV_elevation_3     = 13, // Elevation in degree (1~90)
    GSV_azimuth_3       = 14, // Azimuth in degree (0~359)
    GSV_SNR_3           = 15, // Signal to noise ration in dB-Hz (0~99), empty if not tracking
    GSV_satelliteID_4   = 16, // Satellite ID
    GSV_elevation_4     = 17, // Elevation in degree (1~90)
    GSV_azimuth_4       = 18, // Azimuth in degree (0~359)
    GSV_SNR_4           = 19, // Signal to noise ration in dB-Hz (0~99), empty if not tracking
    GSV_checksum        = 20, // Checksum
    GSV_fieldNum,

}GSV_field;

typedef enum
{
    RMC_MessageID       = 0, // Message ID
    RMC_time            = 1, // Time in format 'hhmmss.ss'
    RMC_status          = 2, // 'V' = Invalif | 'A' = Valid
    RMC_latitude        = 3, // Latitude in format 'ddmm.mmmm' (degrees and minutes)
    RMC_northSouth      = 4, // 'N' = North | 'S' = South
    RMC_Longitude       = 5, // Longitude in format 'ddmm.mmmm' (degrees and minutes)
    RMC_eastWest        = 6, // 'E' = East | 'W' = West
    RMC_speed           = 7, // Speed over ground in knots
    RMC_COG             = 8, // Course over ground in degree
    RMC_date            = 9, // Date in format 'ddmmyy'
    RMC_magneticVariation = 10, // Magnetic variation in degree, not being output
    RMC_magneticEW      = 11, // Magnetic variation E/W indicator, not being output
    RMC_ositioningMode  = 12, // 'N' = No fix | 'A' = Autonomous GNSS fix | D‟=Differential GNSS fix
    RMC_checksum        = 13, // Checksum
    RMC_fieldNum,

}RMC_field;

typedef enum
{
    VTG_MessageID       = 0, // Message ID
    VTG_courseGnd_T     = 1, // Course over ground (true) in degree
    VTG_courseGnd_M     = 3, // Course over ground (magnetic), not being output
    VTG_speed_knots     = 5, // Speed over ground in knots
    VTG_speed_kmh       = 7, // Speed over ground in km/h
    VTG_positioningMode = 9, // 'N'= No fix
                             // 'A'= Autonomous GNSS fix
                             // 'D'= Differential GNSS fix
    VTG_checksum        = 10, // Checksum
    VTG_fieldNum,

}VTG_field;

typedef enum {
    /*GGA-Global Positioning System Fix Data, is the essential fix data which provides 3D location and
     accuracy data*/
    NMEA_MESSAGE_TYPE_GGA             = 0,
    /*GLL-Geographic Latitude and Longitude, which contains position information, time of position fix and
    status*/
    NMEA_MESSAGE_TYPE_GLL             = 1,
    /*GSA-GNSS DOP and Active Satellites, which provides details on the fix and includes the number of
    satellites being used in the current solution and the DOP. At most the first 12 satellite IDs are output*/
    NMEA_MESSAGE_TYPE_GSA             = 2,
    /*GSV-GNSS Satellites in View. One GSV sentence can only provide data for at most 4 satellites, so
    several sentences might be required for full information. Since GSV includes satellites that are not used
    as part of the solution, GSV sentence contains more satellites than GGA does*/
    NMEA_MESSAGE_TYPE_GSV             = 3,
    //RMC-Recommended Minimum Position Data (including position, velocity and time)
    NMEA_MESSAGE_TYPE_RMC             = 4,
    //VTG-Track Made Good and Ground Speed
    NMEA_MESSAGE_TYPE_VTG             = 5,
    NMEA_MESSAGE_TYPE_NUM,

}NMEA_messageType;

typedef enum {
    NMEA_OK,
    NMEA_ERROR,
    NMEA_MESSAGE_ID_ERROR,
    NMEA_INVALID_TALKER,
    NMEA_INVALID_MESSAGE_TYPE,
}NMEA_result;


typedef struct {
    NMEA_talkerType talker;
    NMEA_messageType type;
} NMEA_Header;

typedef Param NMEA_Field;
typedef uint16_t NMEA_LenType;

typedef struct {
    NMEA_Header header;
    NMEA_Field* fields;
    NMEA_LenType fieldCount;
} NMEA_sentence;

NMEA_LenType NMEA_parseSentence(NMEA_sentence* nmea, NMEA_Field* buffer, NMEA_LenType len, char* src);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_NMEA_H_
