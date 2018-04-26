.name "zork"
.comment "comment"

l2:		sti r1, %:live, %1
		and r1 , %00000, r1

live:
		live %1
		zjmp %:live
