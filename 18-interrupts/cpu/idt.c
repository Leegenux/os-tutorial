#include "idt.h"
#include "../kernel/util.h"

void set_idt_gate(int n, u32 handler) {   // This function stuffs a single idt_gate with specified values.
    idt[n].low_offset = low_16(handler);  // idt is a array of idt_gate s.
    idt[n].sel = KERNEL_CS;         
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}

void set_idt() {
    /**
     * It's mainly about setting the address of the IDT array and its size
     * After that, load the IDTs.
     */
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}
