#include <Array.h>
class ILed;
class ILedArray : public Array<ILed*> { 
    public: 
    	/* Adds item to the end of the array. */
    	void append(ILed& item);

    	/* Inserts item at the i-th slot of the array. */
    	void insert(uint16_t index, ILed& item);

    	/*Returns the i-th element from the array, or NULL if invalid. */
    	ILed& get(uint16_t index);

    	/* Removes the i-th element from the array. Returns null if invalid. */
    	ILed& remove(uint16_t index);
};