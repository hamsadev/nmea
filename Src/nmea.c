#include "nmea.h"

#define STR(S)          {S, sizeof(S) - 1}

static void Param_print(Param* param);
static NMEA_result NMEA_parseHeader(NMEA_Header* header, char* src);
static Mem_CmpResult strConst_compare(const void* itemA, const void* itemB, Mem_LenType itemLen);

static const Str TALKERS[TALEKR_NUM] = {
    STR("GP"),  // Global Positioning System (GPS)
    STR("GL"),  // Global Navigation Satellite System (GLONASS)
    STR("GN"),  // Multiple Global Navigation Satellite Systems (e.g., GPS and GLONASS)
    STR("GA"),  // Galileo - European Global Navigation Satellite System
    STR("GB"),  // BeiDou - Chinese Satellite Navigation System
    STR("SB"),  // Other Satellite-Based Positioning System (non-standard)
    STR("II"),  // Internal Inland Navigation System
    STR("IN"),  // Indian Regional Navigation Satellite System
    STR("EX"),  // European Marine-based Navigation System
};

static const Str MESSAGE_PARAM_TYPES[NMEA_MESSAGE_TYPE_NUM] = {
    STR("GGA"),
    STR("GLL"),
    STR("GSA"),
    STR("GSV"),
    STR("RMC"),
    STR("VTG"),
};

NMEA_LenType NMEA_parseSentence(NMEA_sentence* nmea, NMEA_Field* buffer, NMEA_LenType len, char* src){
    Param param;
    Param_Cursor cursor;

    src = Str_ignoreSpecialCharacters(src);
    Param_initCursor(&cursor, src, Str_len(src), ',');

    NMEA_Field* tempBuffer = buffer;
    while(len-- > 0 && Param_next(&cursor, &param)){
        *tempBuffer++ = param;
        #if NMEA_DEBUG
        Param_print(&param);
        #endif // NMEA_DEBUG
    }
    nmea->fieldCount = param.Index + 1;
    NMEA_result error = NMEA_parseHeader(&nmea->header, buffer[0].Value.String);

    return error ? error : nmea->fieldCount;
}

static NMEA_result NMEA_parseHeader(NMEA_Header* header, char* src){
    Str temp;
    Mem_LenType ret;

    temp.Text = src;
    src = Str_ignoreAlphabet(src);
    temp.Len = (Str_LenType)(src - temp.Text);
    if(temp.Len != NMEA_MESSAGE_ID_LENGTH){
        return NMEA_MESSAGE_ID_ERROR;
    }

    temp.Len = NMEA_MESSAGE_TALKER_LENGTH;
    ret = Mem_linearSearch(TALKERS, TALEKR_NUM, sizeof(TALKERS[0]), &temp, strConst_compare);
    if(ret < 0){
        return NMEA_INVALID_TALKER;
    }
    header->talker = (NMEA_talkerType)ret;

    temp.Text += NMEA_MESSAGE_TALKER_LENGTH;
    temp.Len = NMEA_MESSAGE_TYPE_LENGTH;
    ret = Mem_linearSearch(MESSAGE_PARAM_TYPES, NMEA_MESSAGE_TYPE_NUM, sizeof(MESSAGE_PARAM_TYPES[0]), &temp, strConst_compare);
    if(ret < 0){
        return NMEA_INVALID_MESSAGE_TYPE;
    }
    header->type = (NMEA_talkerType)ret;

    return NMEA_OK;
}

static Mem_CmpResult strConst_compare(const void* itemA, const void* itemB, Mem_LenType itemLen) {
  Mem_LenType len = ((StrConst*) itemA)->Len < ((StrConst*) itemB)->Len ? ((StrConst*) itemA)->Len : ((StrConst*) itemB)->Len;
  return memcmp(((StrConst*) itemA)->Text, ((StrConst*) itemB)->Text, len);
}

#if NMEA_DEBUG
static void Param_print(Param* param) {
    static const char* PARAM_TYPES[] = {
        "Unknown",
        "Number",
        "NumberHex",
        "NumberBinary",
        "Float",
        "State",
        "StateKey",
        "Boolean",
        "String",
        "Null",
    };

    PRINTF("{%u, %s, ", param->Index, PARAM_TYPES[(int) param->Value.Type]);
    switch (param->Value.Type) {
        case Param_ValueType_Unknown:
            PRINTF("\"%s\"", param->Value.Unknown);
            break;
        case Param_ValueType_Number:
            PRINTF("%d", param->Value.Number);
            break;
        case Param_ValueType_NumberHex:
            PRINTF("%X", param->Value.NumberHex);
            break;
        case Param_ValueType_NumberBinary:
            PRINTF("%u", param->Value.NumberBinary);
            break;
        case Param_ValueType_Float:
            PRINTF("%f", param->Value.Float);
            break;
        case Param_ValueType_State:
            PRINTF("%s", param->Value.State ? "HIGH" : "LOW");
            break;
        case Param_ValueType_StateKey:
            PRINTF("%s", param->Value.StateKey ? "ON" : "OFF");
            break;
        case Param_ValueType_Boolean:
            PRINTF("%s", param->Value.Boolean ? "true" : "false");
            break;
        case Param_ValueType_String:
            PRINTF("\"%s\"", param->Value.String);
            break;
        case Param_ValueType_Null:
            PRINTF("\"%s\"", param->Value.Null);
            break;
    }
    PRINTLN("}");
}
#endif // NMEA_DEBUG

