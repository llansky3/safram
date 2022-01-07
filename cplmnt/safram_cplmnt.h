
/*
#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
*/

#define FCN_UINT8_CPLMNT(_value) (uint8_t) ~(_value)

#define SAFRAM_SET_UINT8_ARRAY(_name, _idx, _value) \
    do { \
        (_name[_idx]) = (_value); \
		(_name##_cplmnt[_idx]) = FCN_UINT8_CPLMNT(_value); \
    } while(0)

#define SAFRAM_GET_UINT8_ARRAY(_name, _idx, _failcall) \
        ((_name[_idx]) == (uint8_t) ~(_name##_cplmnt[_idx])) ? ( _name[_idx]) : \
	    (_failcall(), (_name[_idx]))

/*
#define SAFRAM_DEF_UINT8_ARRAY(_name, _value) \
    do { \
        __attribute__((section(".data_safram"))) uint8_t _name[] = _value; \
        __attribute__((section(".data_safram_cplmnt"))) uint8_t _name##_cplmnt[_size]; \        
    } while(0)
*/