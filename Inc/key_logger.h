#ifndef __KEY_LOGGER_H
#define __KEY_LOGGER_H
#include "stm324xg_eval_eeprom.h"
#include "data_storage.h"
#include "string.h"
#include "stdbool.h"

#define LINK_KEY_TEST /* Adiciona um campo à estrutura LinkKeyInfo_t para facilitar os testes */


/****************** Remover depois de adicionada a Bluetopia *********************************/
/********* Prototipos das funcoes definidos na bluetopia...?*/

/* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two BD_ADDR_t variables.  This MACRO only returns   */
   /* whether the two BD_ADDR_t variables are equal (MACRO returns      */
   /* boolean result) NOT less than/greater than.  The two parameters to*/
   /* this MACRO are both of type BD_ADDR_t and represent the BD_ADDR_t */
   /* variables to compare.                                             */
#define COMPARE_BD_ADDR(_x, _y) (((_x).BD_ADDR0 == (_y).BD_ADDR0) && ((_x).BD_ADDR1 == (_y).BD_ADDR1) && ((_x).BD_ADDR2 == (_y).BD_ADDR2) && ((_x).BD_ADDR3 == (_y).BD_ADDR3) && ((_x).BD_ADDR4 == (_y).BD_ADDR4) && ((_x).BD_ADDR5 == (_y).BD_ADDR5))

typedef unsigned char Byte_t;                   /* Generic 8 bit Container.   */

/*
NOTA:
No __BTTYPESH__ esta definido o __PACKED_STRUCT_BEGIN__  __PACKED_STRUCT_END__ utilizado nas duas structs seguintes.
*/
   /* The following MACRO is a utility MACRO that exists to assign      */
   /* the individual Byte values into the specified BD_ADDR variable.   */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the BD_ADDR variable in Little Endian Format.  The    */
   /* first parameter is the BD_ADDR variable (of type BD_ADDR_t) to    */
   /* assign, and the next six parameters are the Individual BD_ADDR    */
   /* Byte values to assign to the variable.                            */
#define ASSIGN_BD_ADDR(_dest, _a, _b, _c, _d, _e, _f) \
{                                                     \
   (_dest).BD_ADDR0 = (_f);                           \
   (_dest).BD_ADDR1 = (_e);                           \
   (_dest).BD_ADDR2 = (_d);                           \
   (_dest).BD_ADDR3 = (_c);                           \
   (_dest).BD_ADDR4 = (_b);                           \
   (_dest).BD_ADDR5 = (_a);                           \
}
typedef struct _tagBD_ADDR_t
{
   Byte_t BD_ADDR0;
   Byte_t BD_ADDR1;
   Byte_t BD_ADDR2;
   Byte_t BD_ADDR3;
   Byte_t BD_ADDR4;
   Byte_t BD_ADDR5;
} BD_ADDR_t;

#define BD_ADDR_SIZE                            (sizeof(BD_ADDR_t))

typedef struct _tagLink_Key_t
{
   Byte_t Link_Key0;
   Byte_t Link_Key1;
   Byte_t Link_Key2;
   Byte_t Link_Key3;
   Byte_t Link_Key4;
   Byte_t Link_Key5;
   Byte_t Link_Key6;
   Byte_t Link_Key7;
   Byte_t Link_Key8;
   Byte_t Link_Key9;
   Byte_t Link_Key10;
   Byte_t Link_Key11;
   Byte_t Link_Key12;
   Byte_t Link_Key13;
   Byte_t Link_Key14;
   Byte_t Link_Key15;
} Link_Key_t;

#define LINK_KEY_SIZE                           (sizeof(Link_Key_t))

   /* The following MACRO is a utility MACRO that exists to assign      */
   /* the individual Byte values into the specified Link Key variable.  */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the Link Key variable in Little Endian Format.  The   */
   /* first parameter is the Link Key variable (of type Link_Key_t) to  */
   /* assign, and the next 16 parameters are the Individual Link Key    */
   /* Byte values to assign to the Link Key variable.                   */
#define ASSIGN_LINK_KEY(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                              \
   (_dest).Link_Key0  = (_p); (_dest).Link_Key1  = (_o); (_dest).Link_Key2  = (_n);            \
   (_dest).Link_Key3  = (_m); (_dest).Link_Key4  = (_l); (_dest).Link_Key5  = (_k);            \
   (_dest).Link_Key6  = (_j); (_dest).Link_Key7  = (_i); (_dest).Link_Key8  = (_h);            \
   (_dest).Link_Key9  = (_g); (_dest).Link_Key10 = (_f); (_dest).Link_Key11 = (_e);            \
   (_dest).Link_Key12 = (_d); (_dest).Link_Key13 = (_c); (_dest).Link_Key14 = (_b);            \
   (_dest).Link_Key15 = (_a);                                                                  \
}

/* The following type declaration represents the structure of a      */
/* single Bluetooth Board Address.                                   */	 
typedef struct _tagLinkKeyInfo_t
{
#ifdef LINK_KEY_TEST
	 uint16_t TestValue;	
#endif
   BD_ADDR_t  BD_ADDR;
   Link_Key_t LinkKey;
} LinkKeyInfo_t;	

void KeyLogger_Init(void);
bool KeyLogger_Add(BD_ADDR_t BD_ADDR, Link_Key_t LinkKey);
bool KeyLogger_Get(BD_ADDR_t BD_ADDR, LinkKeyInfo_t* key_bdAddr_str);
bool KeyLogger_Exists(BD_ADDR_t BD_ADDR);
bool KeyLogger_Remove(BD_ADDR_t BD_ADDR);
void KeyLogger_Load(void);
void KeyLogger_Clear(void);
bool KeyLogger_Update(void);

#define EEPROM_KEY_DATA_ADDR 0x50
#define MAX_KEY_DATA 8




#endif
