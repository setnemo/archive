.name "zork"
.comment "I'M ALIIIIVE"
	
l2:		sti r1, %:live, %1
		and r1, %0, r1
		zjmp %:live
		zjmp %:live
		zjmp %:live
		zjmp %:live

live:	live %1
		zjmp %:live
		zjmp %:live2
		zjmp %:live

live2:	live %1
		zjmp %:live
		zjmp %:live2
