
#ifndef CMD_DEF
#define CMD_DEF(a,b)
#define DO_UNDEF_CMD_DEF
#endif

CMD_DEF(SaveDedicatedObjToFile, L"TaskCommands")
CMD_DEF(ChangeColorNoSelect, L"TaskCommands")
CMD_DEF(AssignLayerToLine, L"TaskCommands")

#ifdef DO_UNDEF_CMD_DEF
#undef DO_UNDEF_CMD_DEF
#undef CMD_DEF
#endif