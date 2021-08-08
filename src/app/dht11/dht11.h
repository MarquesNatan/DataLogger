/*============================================================================*/
#ifndef DHT11_H
#define	DHT11_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
/*============================================================================*/
#define DHT11_OK                 0
#define DHT11_ERROR_TIMEOUT      1
#define DHT11_ERROR_CHECKSUM     2
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    uint8_t DHT11_RequestData(void);
    uint8_t DHT11_ReadData( void );
    uint8_t DHT11_ReadByte( void );
    uint8_t* DHT11_GetTemp( void );
    uint8_t* DHT11_GetHum( void );
    
    void DHT11_Start( void );
    void DHT11_Check_Response(void);
    uint8_t read_data (void);
    
    
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* DHT11_H */
/*============================================================================*/
