/**
 * @file nemaSentence.h
 * @author Hamid Salehi (hamsame.dev@gmail.com)
 * @brief Nema sentence header file
 * @version 0.1
 * @date 2022-02-13
 * 
 * @copyright Copyright (c) 2022
 * @copyright Copyright (c) 2022 Hamid Salehi
 * 
 */

#ifndef _GNSS_TYPEDEF_H_
#define _GNSS_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NEMA_MESSAGE_MAX_LENGTH 82

/************************************************************************/
/*  DATAS SEGMENTS TYPEDEFS                                 */
/************************************************************************/
typedef enum GGATag
{
    GGA_MessageID       = 0, // Message ID
    GGA_UTCTime         = 1, // Time in format 'hhmmss.sss'
    GGA_latitude        = 2, // Latitude in format 'ddmm.mmmm' (degrees and minutes)
    GGA_northSouth      = 3, // 'N' = North | 'S' = South
    GGA_Longitude       = 4, // Longitude in format 'ddmm.mmmm' (degrees and minutes)
    GGA_eastWest        = 5, // 'E' = East | 'W' = West
    GGA_fixStatus       = 6, // '0' = Invalid
                             // '1' = GNSS fix
                             // '2' =DGPS fix
                             // '6' =Estimated (dead reckoning) Mode
    GGA_SVNum           = 7, // Number of satellites being used (0~24)
    GGA_HDOP            = 8, // Horizontal dilution of precision
    GGA_atitude         = 9, // Altitude in meters according to WGS84 ellipsoid
    GGA_atitudeUnit     = 10,
    GGA_geoidSeparation = 11, // Height of geoid (means sea level) above WGS84 ellipsoid, meter
    GGA_geoidSeparationUnit =12,
    GGA_DGPS_Age        = 13, // Age of DGPS data in seconds, empty if DGPS is not used
    GGA_DGPS_StationID  = 14, // DGPS station ID, empty if DGPS is not used
    GGA_checksum        = 15, // Checksum

}GGA_sentence;

typedef enum GLLTag
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

}GLL_sentence;

typedef enum GSATag
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
    
}GSA_sentence;

typedef enum GSVTag
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

}GSV_sentence;

typedef enum RMCTag
{
    RMC_MessageID       = 0, // Message ID
    RMC_time            = 1, // Time in format 'hhmmss.ss'
    RMC_dataValid       = 2, // 'V' = Invalif | 'A' = Valid
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

}RMC_sentence;

typedef enum VTGTag
{ 
    VTG_MessageID       = 0, // Message ID
    VTG_courseGnd_T     = 1, // Course over ground (true) in degree
    VTG_courseGnd_M     = 3, // Course over ground (magnetic), not being output
    VTG_speed_knots     = 5, // Speed over ground in knots
    VTG_speed_kmh       = 7, // Speed over ground in km/h
    VTG_positioningMode = 9, // 'N'=No fix
                             // 'A'=Autonomous GNSS fix
                             // 'D'=Differential GNSS fix
    VTG_checksum        = 10, // Checksum

}VTG_sentence;

typedef enum segmentsTag{
    /*GGA-Global Positioning System Fix Data, is the essential fix data which provides 3D location and
     accuracy data*/
    GGA_SEG             = 0,
    /*GLL-Geographic Latitude and Longitude, which contains position information, time of position fix and
    status*/
    GLL_SEG             = 1,
    /*GSA-GNSS DOP and Active Satellites, which provides details on the fix and includes the number of
    satellites being used in the current solution and the DOP. At most the first 12 satellite IDs are output*/
    GSA_SEG             = 2,
    /*GSV-GNSS Satellites in View. One GSV sentence can only provide data for at most 4 satellites, so
    several sentences might be required for full information. Since GSV includes satellites that are not used
    as part of the solution, GSV sentence contains more satellites than GGA does*/
    GSV_SEG             = 3,
    //RMC-Recommended Minimum Position Data (including position, velocity and time)
    RMC_SEG             = 4,
    //VTG-Track Made Good and Ground Speed
    VTG_SEG             = 5,

}gnssSegmentID;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_GNSS_TYPEDEF_H_
