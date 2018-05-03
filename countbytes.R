l2:		sti r1, %:live, %1		#	0b68 0100 0f00 01			1 1 1 2 1		6
		and r1, %0, r1			#	0664 0100 0000 0001			1 1 1 4 1		8
live:	live %1					#	0100 0000 01				1 0 4			5
		zjmp %:live				#	09ff fb						1 0 2			3
								#		0x4 aka 4
		

l2:		sti r1, %:live, %1		#	0b68 0100 0f00 01			1 1 1 2 1		6
		and r1, %0, r1			#	06 6401 0000 0000 01		1 1 1 4 1		8
live:	live %1					#	0100 0000 01				1 0 4			5
		zjmp %:l2				#	09ff ec						1 0 2			3
								#		0x13 aka 19


09ff fb 0900 0009 0000 0900 0001 0000 0001						#my
0900 0009 fffb 0900 0001 0000 0001 0900
0009 0000 

0900 0c 0900 0909 0006 0900 0301 0000 0001						#original
09ff fb09 0006 09ff f501 0000 0001 09ff
ed09 fff8 


l2:		sti r1, %:live, %1		#	0b68 0100 1b00 01			1 1 1 2 1		6
		and r1, %0, r1			#	0664 0100 0000 0001			1 1 1 4 1		8
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

l2:		sti r1, %:live, %1		#	0b68 0100 1b00 01			1 1 1 2 1		6
		and r1, %0, r1			#	0664 0100 0000 0001			1 1 1 4 1		8
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