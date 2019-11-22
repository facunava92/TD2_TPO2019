//void main(void){
//__asm__(
//"_start:\n\t"
//"	B inicio\n\t"
//"inicio:\n\t"
//"	MOV R0, #0x6 @ Inicializo cuanto delay voy a hacer, en un programa real recibiria esto por otra funcion\n\t"
//"retardo:\n\t"
//"	SUBS R0, R0, #0x1 @ Utilizo el contador descendiente para llevar la cuenta de cuantos\n\t"
//"			  @   retardos me faltan, y para hacer el retardo en si\n\t"
//"	BNE retardo	  @ Si todavia no lleve el contador a 0, sigo retardando\n\t"
//"final:\n\t"
//"	B final		  @ Esto es para que si el programa se ejecuta fuera de un debugger, no tire segfault\n\t"
//);
//}
