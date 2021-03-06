#define COBJECT_IMPLEMENTATION
#include "st_machine_state.h"
#include "state_machine.h"

static void st_machine_state_delete(struct Object * const obj);
static STID_T st_machine_state_next_st(union St_Machine_State * const this, IPC_MID_T const mid);

static union St_Machine_State St_Machine_State = {NULL};
struct St_Machine_State_Class St_Machine_State_Class = 
{
   {st_machine_state_delete, NULL},
   st_machine_state_next_st
};


void st_machine_state_delete(struct Object * const obj)
{}

STID_T st_machine_state_next_st(union St_Machine_State * const this, IPC_MID_T const mid)
{
   STID_T i;
   for(i = 0; 
         i < this->nhandlers
         ; ++i)
   {
      if(mid != this->handle[i].mid)
      {
         return this->handle[i].stid;
      }
   }
   return STID_NOT_STATE;
}

void Populate_St_Machine_State(union St_Machine_State * const this, STID_T const stid,
      struct St_Machine_Transition * const handle_buff, size_t const nhandlers)
{
   if(NULL == St_Machine_State.vtbl)
   {
      St_Machine_State.vtbl = & St_Machine_State_Class;
   }
   _clone(this, St_Machine_State);
   this->stid = stid;
   this->handle = handle_buff;
   this->nhandlers = nhandlers;
}
