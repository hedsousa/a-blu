#include "key_logger.h"

//#define KEY_LOGGER_PRINT_ERROR /* Usar se definidas funcoes para o lcd. */

static int KeyLogger_Scan(BD_ADDR_t BD_ADDR);
static BD_ADDR_t BD_ADDR_EMPTY;
LinkKeyInfo_t KeyData[MAX_KEY_DATA];
/**
*	Iniciacao da EEPROM e estrutura (array) com informacao das Keys associadas aos BD_ADDR
* Carrega o array da EEPROM para uma variavel global (KeyData[]) funcionando assim como cache para mais rapido acesso.
*/
void KeyLogger_Init(){
	DataStorage_Init(); /* Preparar EEPROM 							*/
	
#ifdef EEPROM_FIRST_READ
	KeyLogger_Update();
#endif	
	KeyLogger_Load();   /* Carrega a estrutura da EEPROM */
	ASSIGN_BD_ADDR(BD_ADDR_EMPTY, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}



/**
* Adiciona um novo BD_ADDR e respetiva LinkKey ao array KeyData e atualiza a EEPROM.
* TODO: Se tiver cheio o que fazer?
*/
bool KeyLogger_Add(BD_ADDR_t BD_ADDR, Link_Key_t LinkKey){
	int index;
//	bool has_changed = false;
	
	index = KeyLogger_Scan(BD_ADDR); 
	if(index != -1){ 			// Se o BD_ADDR ja existir substitui a chave anterior pela nova chave
		KeyData[index].LinkKey = LinkKey;
		KeyLogger_Update();
		return true;

	}else{
		index = KeyLogger_Scan(BD_ADDR_EMPTY);
		if(index != -1){
		
			KeyData[index].BD_ADDR = BD_ADDR;
			KeyData[index].LinkKey = LinkKey;
			KeyLogger_Update();
			return true;
		}
	}
	return false;
}

/**
*	Devolve em "get_bdAddr_key" a estrutura associada ao BD_ADDR, se existir.
*/
bool KeyLogger_Get(BD_ADDR_t BD_ADDR, LinkKeyInfo_t* get_bdAddr_key){ // Poderá devolver apenas a linkKey....por agora da jeito devolver tudo
	int index;
	
	index = KeyLogger_Scan(BD_ADDR);
	if(index != -1){
		*get_bdAddr_key = KeyData[index];
		return true;
	}
	return false;
}

/**
*	Informa se o BD_ADDR existe na KeyData
*/
bool KeyLogger_Exists(BD_ADDR_t BD_ADDR){
	LinkKeyInfo_t dummy; /* Para reutilizar a funcao KeyLogger_Get() e aproveitar apenas retorno  */
	//return KeyLogger_Get(BD_ADDR, &dummy) != -1? true : false;
	return KeyLogger_Get(BD_ADDR, &dummy);
}
	
/**
*	Remove a estrutura associada ao BD_ADDR no KeyData e atualiza a EERPOM
*/
bool KeyLogger_Remove(BD_ADDR_t BD_ADDR){
	int index;
	
	index = KeyLogger_Scan(BD_ADDR);
	if(index != -1){
		memset((LinkKeyInfo_t*)(KeyData+index),0,sizeof(LinkKeyInfo_t)); //Confirmar isto!!!
		KeyLogger_Update();
		return true;
	}
	return false;
}

/**
* Carrega da eeprom a estrutura Key_Data na posicao 
	EEPROM_KEY_DATA_ADDR (definido no key_logger.h)
				
				Nota: 
						Deve ser utilizada depois do KeyLogger_Init(). 
*/
void KeyLogger_Load(){
	DataStorage_Load(EEPROM_KEY_DATA_ADDR, KeyData);
}	

/**
* Procura pelo BD_ADDR. Se encontrar devolve o indice no array KeyData, caso contrario devolve -1
*/
int KeyLogger_Scan(BD_ADDR_t BD_ADDR){
	int i;
	
	for(i = 0; i < MAX_KEY_DATA; i++){
		if(COMPARE_BD_ADDR(BD_ADDR, KeyData[i].BD_ADDR)){ 
			return i;
		}
	}
	return -1;
}

/**
* Guarda na eeprom toda a estrutura Key_Data
*/
bool KeyLogger_Update(){
	uint16_t status = EEPROM_OK;
	//Guardar estrutura em memoria
	status = DataStorage_Save(EEPROM_KEY_DATA_ADDR, KeyData, sizeof(KeyData));  // sizeof(Equivalente a LinkKeyInfo_t*MAX_KEY_DATA)
	if(status != EEPROM_OK){
#ifdef KEY_LOGGER_PRINT_ERROR
		LCD_PrintError("KeyLogger_Update()");
#endif		
		return false;
	}
	return true;
}

/**
* Limpa toda a estrutura Key_Data guardada na eeprom
* 		Nota:
					Pode ser util se utilizar um botao para fazer reset a eeprom
*/
void KeyLogger_Clear(){	
	memset(KeyData,0, sizeof(KeyData));
	if(KeyLogger_Update()){
#ifdef KEY_LOGGER_PRINT_ERROR
		BSP_LCD_Clear(LCD_COLOR_CYAN);
		BSP_LCD_DisplayStringAtLine(1,(uint8_t*)"EEPROM Cleared");
	}else{

		LCD_PrintError("KeyLogger_Clear()");
#endif		
	}
}
