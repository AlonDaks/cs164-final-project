#include <ILedArray.h>
#include <Led.h>

// SimpleLed invalid;

void ILedArray::append(ILed& item){
	Array<ILed*>::append(&item);
} 

void ILedArray::insert(uint16_t index, ILed& item) {
	Array<ILed*>::insert(index, &item);

}

// ILed& ILedArray::get(uint16_t index) {
// 	ILed* storedILED =Array<ILed*>::get(index)
// 	if(storedILED == NULL){
// 		return invalid;
// 	}
// 	return *storedILED;	
// }

// ILed& ILedArray::remove(uint16_t index) {
// 	ILed* storedILED =Array<ILed*>::remove(index)
// 	if(storedILED == NULL){
// 		return invalid;
// 	}
// 	return *storedILED;	
// }
