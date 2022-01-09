#ifndef SAFRAM_CPLMNT_H
#define SAFRAM_CPLMNT_H

/* Macros for UINT8 arrays
   - single variable or other types could be covered with similar macros
*/

#define SAFRAM_DEF_UINT8_ARRAY(_name) __attribute__((section(".data_safram"))) uint8_t _name[]
#define SAFRAM_DEF_UINT8_ARRAY_CPLMNT(_name) __attribute__((section(".data_safram_cplmnt"))) uint8_t _name##_cplmnt[]

#define FCN_UINT8_CPLMNT(_value) ((uint8_t) ~(_value))

#define SAFRAM_SET_UINT8_ARRAY(_name, _idx, _value) \
    do { \
        (_name[_idx]) = (_value); \
		(_name##_cplmnt[_idx]) = FCN_UINT8_CPLMNT(_value); \
    } while(0)

#define SAFRAM_GET_UINT8_ARRAY(_name, _idx, _failcall) \
        ((_name[_idx]) == FCN_UINT8_CPLMNT(_name##_cplmnt[_idx])) ? ( _name[_idx]) : \
	    (_failcall, (_name[_idx]))

/*  Memory addresses for both sections of safety RAM 
    - these will be supplied during linking
    - these are not required for protection and checking really 
*/

// Memory section where the variables are stored
extern uint32_t _DATA_SAFRAM_START;
extern uint32_t _DATA_SAFRAM_END;

#define PTR_UINT8_SAFRAM_START (uint8_t*)&_DATA_SAFRAM_START
#define PTR_UINT8_SAFRAM_END   (uint8_t*)&_DATA_SAFRAM_END 

// Memory section where the variables one's complements are stored
extern uint32_t _DATA_SAFRAM_CPLMNT_START;
extern uint32_t _DATA_SAFRAM_CPLMNT_END;

#define PTR_UINT8_SAFRAM_CPLMNT_START (uint8_t*)&_DATA_SAFRAM_CPLMNT_START
#define PTR_UINT8_SAFRAM_CPLMNT_END   (uint8_t*)&_DATA_SAFRAM_CPLMNT_END 

#endif /* SAFRAM_CPLMNT_H */