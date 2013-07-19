
/* #line 1 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
#include "pch.h"
#include "jancyhighlighter.h"
#include "moc_jancyhighlighter.cpp"

//.............................................................................


/* #line 2 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
static const char _jancy_lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 9, 1, 
	10, 1, 11, 1, 12, 1, 13, 1, 
	14, 1, 15, 1, 16, 1, 17, 1, 
	18, 1, 19, 1, 20, 1, 21, 1, 
	22, 1, 23, 1, 24, 1, 25, 1, 
	26, 1, 27, 1, 28, 2, 2, 3, 
	2, 2, 4, 2, 2, 5, 2, 2, 
	6, 2, 2, 7, 2, 2, 8
};

static const short _jancy_lexer_key_offsets[] = {
	0, 3, 6, 13, 16, 50, 53, 56, 
	57, 60, 61, 63, 64, 68, 70, 71, 
	77, 84, 94, 102, 110, 118, 126, 134, 
	142, 150, 158, 166, 174, 182, 191, 199, 
	207, 217, 226, 234, 242, 250, 258, 266, 
	274, 282, 290, 298, 306, 314, 322, 330, 
	338, 346, 354, 366, 374, 382, 390, 398, 
	406, 414, 422, 430, 439, 447, 455, 463, 
	471, 479, 487, 496, 506, 514, 522, 530, 
	538, 546, 554, 562, 573, 581, 589, 597, 
	605, 613, 621, 629, 637, 645, 657, 665, 
	673, 681, 689, 697, 705, 713, 721, 729, 
	737, 745, 753, 762, 771, 779, 787, 795, 
	807, 815, 823, 831, 839, 847, 856, 864, 
	872, 880, 888, 896, 906, 914, 922, 930, 
	938, 946, 954, 962, 970, 978, 989, 997, 
	1005, 1013, 1022, 1030, 1038, 1046, 1054, 1062, 
	1070, 1078, 1086, 1094, 1102, 1110, 1118, 1126, 
	1137, 1145, 1153, 1161, 1169, 1177, 1185, 1194, 
	1202, 1210, 1218, 1226, 1235, 1244, 1252, 1260, 
	1268, 1276, 1284, 1292, 1300, 1308, 1316, 1324, 
	1332, 1340, 1349, 1357, 1365, 1373, 1381, 1389, 
	1397, 1408, 1418, 1426, 1434, 1442, 1450, 1460, 
	1469, 1477, 1485, 1493, 1501, 1509, 1517, 1525, 
	1535, 1544, 1553, 1561, 1569, 1577, 1585, 1594, 
	1602, 1612, 1621, 1630, 1638, 1646, 1654, 1662, 
	1670, 1680, 1688, 1696, 1704, 1712, 1720, 1728, 
	1736, 1745, 1753, 1761, 1769, 1778, 1780
};

static const char _jancy_lexer_trans_keys[] = {
	10, 34, 92, 10, 39, 92, 34, 48, 
	57, 65, 70, 97, 102, 10, 34, 92, 
	9, 10, 13, 32, 34, 39, 47, 48, 
	95, 97, 98, 99, 100, 101, 102, 103, 
	104, 105, 109, 110, 111, 112, 114, 115, 
	116, 117, 118, 119, 49, 57, 65, 90, 
	106, 122, 9, 13, 32, 10, 34, 92, 
	10, 10, 39, 92, 10, 42, 47, 10, 
	88, 120, 48, 57, 48, 57, 10, 48, 
	57, 65, 70, 97, 102, 95, 48, 57, 
	65, 90, 97, 122, 95, 98, 108, 117, 
	48, 57, 65, 90, 97, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 99, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	103, 48, 57, 65, 90, 97, 122, 95, 
	118, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	105, 111, 114, 48, 57, 65, 90, 97, 
	122, 95, 103, 110, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 100, 48, 57, 65, 90, 
	97, 122, 95, 105, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 100, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 98, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 107, 48, 57, 65, 90, 
	97, 122, 95, 97, 100, 104, 108, 111, 
	48, 57, 65, 90, 98, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 99, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 115, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 115, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	114, 48, 57, 65, 90, 97, 122, 95, 
	117, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	110, 48, 57, 65, 90, 97, 122, 95, 
	117, 48, 57, 65, 90, 97, 122, 95, 
	101, 111, 48, 57, 65, 90, 97, 122, 
	95, 102, 108, 115, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 116, 48, 57, 65, 90, 
	97, 122, 95, 116, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 108, 110, 118, 120, 48, 
	57, 65, 90, 97, 122, 95, 117, 48, 
	57, 65, 90, 97, 122, 95, 109, 48, 
	57, 65, 90, 97, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 100, 48, 
	57, 65, 90, 97, 122, 95, 97, 108, 
	111, 114, 117, 48, 57, 65, 90, 98, 
	122, 95, 108, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 99, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 112, 48, 57, 65, 90, 97, 
	122, 95, 102, 110, 48, 57, 65, 90, 
	97, 122, 95, 100, 116, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 120, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 49, 51, 54, 56, 95, 
	112, 48, 57, 65, 90, 97, 122, 54, 
	95, 48, 57, 65, 90, 97, 122, 50, 
	95, 48, 57, 65, 90, 97, 122, 52, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	117, 48, 57, 65, 90, 97, 122, 95, 
	108, 116, 48, 57, 65, 90, 97, 122, 
	95, 116, 48, 57, 65, 90, 97, 122, 
	95, 105, 48, 57, 65, 90, 97, 122, 
	95, 99, 48, 57, 65, 90, 97, 122, 
	95, 97, 48, 57, 65, 90, 98, 122, 
	95, 115, 48, 57, 65, 90, 97, 122, 
	95, 97, 101, 117, 48, 57, 65, 90, 
	98, 122, 95, 109, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 115, 48, 57, 65, 90, 
	97, 122, 95, 112, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 99, 48, 57, 65, 90, 
	97, 122, 95, 119, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 98, 110, 112, 118, 48, 
	57, 65, 90, 97, 122, 95, 106, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 101, 104, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	48, 57, 65, 90, 98, 122, 95, 116, 
	48, 57, 65, 90, 97, 122, 95, 111, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 114, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 100, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	111, 114, 117, 48, 57, 65, 90, 98, 
	122, 95, 99, 48, 57, 65, 90, 97, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 102, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 120, 48, 57, 65, 90, 97, 
	122, 95, 101, 111, 48, 57, 65, 90, 
	97, 122, 95, 99, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 115, 48, 57, 65, 90, 
	97, 122, 95, 112, 116, 48, 57, 65, 
	90, 97, 122, 95, 101, 118, 48, 57, 
	65, 90, 97, 122, 95, 114, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 121, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 99, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 98, 48, 57, 
	65, 90, 97, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 97, 116, 48, 
	57, 65, 90, 98, 122, 95, 100, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 117, 48, 
	57, 65, 90, 97, 122, 95, 114, 48, 
	57, 65, 90, 97, 122, 95, 101, 105, 
	116, 119, 48, 57, 65, 90, 97, 122, 
	95, 103, 108, 122, 48, 57, 65, 90, 
	97, 121, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 111, 48, 57, 65, 90, 
	97, 122, 95, 102, 48, 57, 65, 90, 
	97, 122, 95, 97, 100, 114, 48, 57, 
	65, 90, 98, 122, 95, 99, 116, 48, 
	57, 65, 90, 97, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 105, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 104, 48, 
	57, 65, 90, 97, 122, 95, 104, 114, 
	121, 48, 57, 65, 90, 97, 122, 95, 
	105, 114, 48, 57, 65, 90, 97, 122, 
	95, 110, 115, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 112, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 100, 111, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 104, 110, 115, 48, 57, 
	65, 90, 97, 122, 95, 105, 115, 48, 
	57, 65, 90, 97, 122, 95, 97, 105, 
	48, 57, 65, 90, 98, 122, 95, 102, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 105, 
	48, 57, 65, 90, 97, 122, 95, 110, 
	48, 57, 65, 90, 97, 122, 95, 103, 
	48, 57, 65, 90, 97, 122, 95, 97, 
	105, 111, 48, 57, 65, 90, 98, 122, 
	95, 114, 48, 57, 65, 90, 97, 122, 
	95, 105, 48, 57, 65, 90, 97, 122, 
	95, 97, 48, 57, 65, 90, 98, 122, 
	95, 114, 48, 57, 65, 90, 97, 122, 
	95, 116, 48, 57, 65, 90, 97, 122, 
	95, 117, 48, 57, 65, 90, 97, 122, 
	95, 97, 48, 57, 65, 90, 98, 122, 
	95, 105, 108, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 101, 104, 48, 57, 65, 90, 
	97, 122, 10, 42, 47, 0
};

static const char _jancy_lexer_single_lengths[] = {
	3, 3, 1, 3, 28, 3, 3, 1, 
	3, 1, 2, 1, 2, 0, 1, 0, 
	1, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	4, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 6, 2, 2, 2, 2, 2, 
	2, 2, 2, 3, 2, 2, 2, 2, 
	2, 2, 3, 4, 2, 2, 2, 2, 
	2, 2, 2, 5, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 6, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 3, 3, 2, 2, 2, 6, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 4, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 5, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 5, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 3, 3, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	5, 4, 2, 2, 2, 2, 4, 3, 
	2, 2, 2, 2, 2, 2, 2, 4, 
	3, 3, 2, 2, 2, 2, 3, 2, 
	4, 3, 3, 2, 2, 2, 2, 2, 
	4, 2, 2, 2, 2, 2, 2, 2, 
	3, 2, 2, 2, 3, 2, 1
};

static const char _jancy_lexer_range_lengths[] = {
	0, 0, 3, 0, 3, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 0, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 0, 0
};

static const short _jancy_lexer_index_offsets[] = {
	0, 4, 8, 13, 17, 49, 53, 57, 
	59, 63, 65, 68, 70, 74, 76, 78, 
	82, 87, 95, 101, 107, 113, 119, 125, 
	131, 137, 143, 149, 155, 161, 168, 174, 
	180, 188, 195, 201, 207, 213, 219, 225, 
	231, 237, 243, 249, 255, 261, 267, 273, 
	279, 285, 291, 301, 307, 313, 319, 325, 
	331, 337, 343, 349, 356, 362, 368, 374, 
	380, 386, 392, 399, 407, 413, 419, 425, 
	431, 437, 443, 449, 458, 464, 470, 476, 
	482, 488, 494, 500, 506, 512, 522, 528, 
	534, 540, 546, 552, 558, 564, 570, 576, 
	582, 588, 594, 601, 608, 614, 620, 626, 
	636, 642, 648, 654, 660, 666, 673, 679, 
	685, 691, 697, 703, 711, 717, 723, 729, 
	735, 741, 747, 753, 759, 765, 774, 780, 
	786, 792, 799, 805, 811, 817, 823, 829, 
	835, 841, 847, 853, 859, 865, 871, 877, 
	886, 892, 898, 904, 910, 916, 922, 929, 
	935, 941, 947, 953, 960, 967, 973, 979, 
	985, 991, 997, 1003, 1009, 1015, 1021, 1027, 
	1033, 1039, 1046, 1052, 1058, 1064, 1070, 1076, 
	1082, 1091, 1099, 1105, 1111, 1117, 1123, 1131, 
	1138, 1144, 1150, 1156, 1162, 1168, 1174, 1180, 
	1188, 1195, 1202, 1208, 1214, 1220, 1226, 1233, 
	1239, 1247, 1254, 1261, 1267, 1273, 1279, 1285, 
	1291, 1299, 1305, 1311, 1317, 1323, 1329, 1335, 
	1341, 1348, 1354, 1360, 1366, 1373, 1376
};

static const unsigned char _jancy_lexer_indicies[] = {
	2, 2, 3, 1, 2, 2, 5, 4, 
	7, 8, 8, 8, 6, 9, 9, 10, 
	7, 12, 13, 12, 12, 14, 15, 16, 
	17, 19, 20, 21, 22, 23, 24, 25, 
	26, 27, 28, 29, 30, 31, 32, 33, 
	34, 35, 36, 37, 38, 18, 19, 19, 
	11, 12, 12, 12, 39, 2, 2, 3, 
	1, 41, 1, 2, 2, 5, 4, 41, 
	4, 42, 43, 40, 44, 43, 46, 46, 
	18, 45, 18, 45, 47, 7, 8, 8, 
	8, 48, 19, 19, 19, 19, 0, 19, 
	50, 51, 52, 19, 19, 19, 49, 19, 
	53, 19, 19, 19, 49, 19, 54, 19, 
	19, 19, 49, 19, 55, 19, 19, 19, 
	49, 19, 56, 19, 19, 19, 49, 19, 
	57, 19, 19, 19, 49, 19, 58, 19, 
	19, 19, 49, 19, 59, 19, 19, 19, 
	49, 19, 60, 19, 19, 19, 49, 19, 
	58, 19, 19, 19, 49, 19, 61, 19, 
	19, 19, 49, 19, 62, 19, 19, 19, 
	49, 19, 64, 26, 19, 19, 19, 63, 
	19, 58, 19, 19, 19, 49, 19, 57, 
	19, 19, 19, 49, 19, 65, 66, 67, 
	19, 19, 19, 49, 19, 68, 69, 19, 
	19, 19, 49, 19, 70, 19, 19, 19, 
	49, 19, 71, 19, 19, 19, 49, 19, 
	72, 19, 19, 19, 49, 19, 73, 19, 
	19, 19, 49, 19, 74, 19, 19, 19, 
	49, 19, 58, 19, 19, 19, 49, 19, 
	75, 19, 19, 19, 49, 19, 76, 19, 
	19, 19, 0, 19, 77, 19, 19, 19, 
	49, 19, 78, 19, 19, 19, 49, 19, 
	58, 19, 19, 19, 49, 19, 79, 19, 
	19, 19, 49, 19, 58, 19, 19, 19, 
	49, 19, 80, 19, 19, 19, 49, 19, 
	81, 19, 19, 19, 49, 19, 58, 19, 
	19, 19, 49, 19, 82, 83, 84, 85, 
	86, 19, 19, 19, 49, 19, 78, 19, 
	19, 19, 49, 19, 87, 19, 19, 19, 
	49, 19, 79, 19, 19, 19, 49, 19, 
	88, 19, 19, 19, 49, 19, 58, 19, 
	19, 19, 49, 19, 89, 19, 19, 19, 
	49, 19, 60, 19, 19, 19, 49, 19, 
	90, 19, 19, 19, 49, 19, 91, 92, 
	19, 19, 19, 49, 19, 93, 19, 19, 
	19, 49, 19, 94, 19, 19, 19, 0, 
	19, 56, 19, 19, 19, 49, 19, 95, 
	19, 19, 19, 49, 19, 96, 19, 19, 
	19, 49, 19, 78, 19, 19, 19, 49, 
	19, 97, 98, 19, 19, 19, 49, 19, 
	99, 100, 101, 19, 19, 19, 49, 19, 
	102, 19, 19, 19, 49, 19, 103, 19, 
	19, 19, 49, 19, 57, 19, 19, 19, 
	49, 19, 104, 19, 19, 19, 49, 19, 
	78, 19, 19, 19, 49, 19, 105, 19, 
	19, 19, 49, 19, 76, 19, 19, 19, 
	63, 19, 82, 106, 107, 108, 19, 19, 
	19, 49, 19, 109, 19, 19, 19, 49, 
	19, 110, 19, 19, 19, 49, 19, 58, 
	19, 19, 19, 0, 19, 111, 19, 19, 
	19, 49, 19, 57, 19, 19, 19, 49, 
	19, 112, 19, 19, 19, 49, 19, 113, 
	19, 19, 19, 49, 19, 114, 19, 19, 
	19, 49, 19, 58, 19, 19, 19, 49, 
	19, 115, 116, 88, 117, 118, 19, 19, 
	19, 49, 19, 82, 19, 19, 19, 49, 
	19, 119, 19, 19, 19, 49, 19, 57, 
	19, 19, 19, 49, 19, 112, 19, 19, 
	19, 49, 19, 120, 19, 19, 19, 49, 
	19, 121, 19, 19, 19, 49, 19, 122, 
	19, 19, 19, 49, 19, 123, 19, 19, 
	19, 49, 19, 74, 19, 19, 19, 49, 
	19, 124, 19, 19, 19, 49, 19, 125, 
	19, 19, 19, 49, 19, 58, 19, 19, 
	19, 49, 19, 58, 126, 19, 19, 19, 
	49, 19, 127, 128, 19, 19, 19, 49, 
	19, 129, 19, 19, 19, 49, 19, 130, 
	19, 19, 19, 49, 19, 114, 19, 19, 
	19, 49, 131, 132, 133, 58, 19, 134, 
	19, 19, 19, 63, 58, 19, 19, 19, 
	19, 49, 58, 19, 19, 19, 19, 49, 
	58, 19, 19, 19, 19, 49, 19, 88, 
	19, 19, 19, 49, 19, 135, 19, 19, 
	19, 49, 19, 136, 75, 19, 19, 19, 
	49, 19, 137, 19, 19, 19, 49, 19, 
	138, 19, 19, 19, 49, 19, 139, 19, 
	19, 19, 49, 19, 140, 19, 19, 19, 
	49, 19, 57, 19, 19, 19, 49, 19, 
	141, 142, 143, 19, 19, 19, 49, 19, 
	144, 19, 19, 19, 49, 19, 145, 19, 
	19, 19, 49, 19, 146, 19, 19, 19, 
	49, 19, 147, 19, 19, 19, 49, 19, 
	148, 19, 19, 19, 49, 19, 78, 19, 
	19, 19, 49, 19, 58, 19, 19, 19, 
	49, 19, 149, 19, 19, 19, 49, 19, 
	150, 19, 19, 19, 49, 19, 151, 152, 
	153, 154, 19, 19, 19, 49, 19, 155, 
	19, 19, 19, 49, 19, 56, 19, 19, 
	19, 49, 19, 156, 19, 19, 19, 49, 
	19, 58, 157, 19, 19, 19, 49, 19, 
	158, 19, 19, 19, 49, 19, 159, 19, 
	19, 19, 49, 19, 78, 19, 19, 19, 
	49, 19, 160, 19, 19, 19, 49, 19, 
	161, 19, 19, 19, 49, 19, 162, 19, 
	19, 19, 49, 19, 163, 19, 19, 19, 
	49, 19, 88, 19, 19, 19, 49, 19, 
	164, 19, 19, 19, 49, 19, 165, 19, 
	19, 19, 49, 19, 166, 19, 19, 19, 
	49, 19, 167, 19, 19, 19, 49, 19, 
	78, 19, 19, 19, 49, 19, 168, 169, 
	170, 171, 19, 19, 19, 49, 19, 81, 
	19, 19, 19, 49, 19, 172, 19, 19, 
	19, 49, 19, 173, 19, 19, 19, 49, 
	19, 174, 19, 19, 19, 49, 19, 175, 
	19, 19, 19, 49, 19, 58, 19, 19, 
	19, 49, 19, 176, 177, 19, 19, 19, 
	49, 19, 178, 19, 19, 19, 49, 19, 
	179, 19, 19, 19, 49, 19, 180, 19, 
	19, 19, 49, 19, 101, 19, 19, 19, 
	49, 19, 181, 182, 19, 19, 19, 49, 
	19, 183, 184, 19, 19, 19, 49, 19, 
	185, 19, 19, 19, 49, 19, 186, 19, 
	19, 19, 49, 19, 58, 19, 19, 19, 
	49, 19, 187, 19, 19, 19, 49, 19, 
	96, 19, 19, 19, 49, 19, 188, 19, 
	19, 19, 49, 19, 189, 19, 19, 19, 
	49, 19, 130, 19, 19, 19, 49, 19, 
	190, 19, 19, 19, 49, 19, 191, 19, 
	19, 19, 49, 19, 192, 19, 19, 19, 
	49, 19, 193, 19, 19, 19, 49, 19, 
	194, 195, 19, 19, 19, 49, 19, 196, 
	19, 19, 19, 49, 19, 197, 19, 19, 
	19, 49, 19, 198, 19, 19, 19, 49, 
	19, 186, 19, 19, 19, 49, 19, 199, 
	19, 19, 19, 49, 19, 74, 19, 19, 
	19, 49, 19, 57, 200, 201, 202, 19, 
	19, 19, 49, 19, 203, 107, 204, 19, 
	19, 19, 49, 19, 130, 19, 19, 19, 
	49, 19, 205, 19, 19, 19, 49, 19, 
	206, 19, 19, 19, 49, 19, 58, 19, 
	19, 19, 49, 19, 207, 208, 94, 19, 
	19, 19, 49, 19, 81, 191, 19, 19, 
	19, 49, 19, 209, 19, 19, 19, 49, 
	19, 210, 19, 19, 19, 49, 19, 79, 
	19, 19, 19, 49, 19, 211, 19, 19, 
	19, 49, 19, 212, 19, 19, 19, 49, 
	19, 213, 19, 19, 19, 49, 19, 58, 
	19, 19, 19, 49, 19, 214, 96, 215, 
	19, 19, 19, 49, 19, 216, 217, 19, 
	19, 19, 49, 19, 58, 58, 19, 19, 
	19, 49, 19, 218, 19, 19, 19, 49, 
	19, 114, 19, 19, 19, 49, 19, 219, 
	19, 19, 19, 49, 19, 220, 19, 19, 
	19, 49, 19, 221, 206, 19, 19, 19, 
	49, 19, 206, 19, 19, 19, 49, 19, 
	27, 222, 223, 19, 19, 19, 49, 19, 
	123, 224, 19, 19, 19, 49, 19, 225, 
	226, 19, 19, 19, 49, 19, 78, 19, 
	19, 19, 49, 19, 203, 19, 19, 19, 
	49, 19, 227, 19, 19, 19, 49, 19, 
	228, 19, 19, 19, 49, 19, 58, 19, 
	19, 19, 49, 19, 229, 230, 231, 19, 
	19, 19, 49, 19, 232, 19, 19, 19, 
	49, 19, 233, 19, 19, 19, 49, 19, 
	111, 19, 19, 19, 49, 19, 234, 19, 
	19, 19, 49, 19, 235, 19, 19, 19, 
	49, 19, 236, 19, 19, 19, 49, 19, 
	79, 19, 19, 19, 49, 19, 114, 237, 
	19, 19, 19, 49, 19, 238, 19, 19, 
	19, 49, 19, 239, 19, 19, 19, 49, 
	19, 77, 19, 19, 19, 49, 19, 80, 
	239, 19, 19, 19, 49, 241, 242, 240, 
	244, 243, 0
};

static const unsigned char _jancy_lexer_trans_targs[] = {
	4, 0, 4, 7, 1, 9, 4, 3, 
	15, 4, 14, 4, 5, 4, 6, 8, 
	10, 12, 13, 16, 17, 32, 50, 66, 
	75, 85, 31, 95, 98, 108, 115, 125, 
	143, 168, 176, 191, 200, 208, 220, 4, 
	4, 4, 4, 11, 4, 4, 2, 4, 
	4, 4, 18, 24, 27, 19, 20, 21, 
	22, 23, 16, 25, 26, 28, 29, 4, 
	30, 33, 45, 47, 34, 40, 35, 36, 
	37, 38, 39, 41, 42, 43, 44, 46, 
	48, 49, 51, 52, 54, 56, 58, 53, 
	55, 57, 59, 60, 63, 61, 62, 64, 
	65, 67, 74, 68, 71, 73, 69, 70, 
	72, 61, 76, 79, 81, 77, 78, 80, 
	82, 83, 84, 86, 87, 89, 90, 88, 
	91, 92, 93, 94, 96, 97, 99, 100, 
	103, 101, 102, 104, 105, 106, 107, 109, 
	110, 111, 112, 113, 114, 116, 122, 123, 
	117, 118, 119, 120, 121, 124, 41, 126, 
	128, 133, 138, 127, 129, 130, 131, 132, 
	134, 135, 136, 137, 139, 140, 141, 142, 
	144, 145, 150, 165, 146, 147, 148, 149, 
	151, 155, 152, 153, 154, 156, 162, 157, 
	160, 158, 159, 161, 163, 164, 166, 167, 
	78, 169, 170, 174, 171, 172, 173, 175, 
	177, 182, 187, 178, 179, 180, 181, 183, 
	184, 185, 186, 188, 189, 190, 192, 196, 
	193, 194, 195, 197, 198, 199, 201, 205, 
	202, 203, 204, 206, 207, 209, 212, 216, 
	210, 211, 213, 214, 215, 217, 218, 219, 
	221, 221, 222, 221, 221
};

static const char _jancy_lexer_trans_actions[] = {
	35, 0, 5, 51, 0, 51, 33, 0, 
	0, 7, 57, 13, 0, 11, 60, 60, 
	0, 54, 0, 48, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 29, 
	31, 19, 9, 0, 27, 21, 0, 25, 
	23, 17, 0, 0, 0, 0, 0, 0, 
	0, 0, 45, 0, 0, 0, 0, 15, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 48, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 45, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 48, 0, 0, 0, 0, 45, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 45, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	48, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	39, 37, 0, 43, 41
};

static const char _jancy_lexer_to_state_actions[] = {
	0, 0, 0, 0, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 0
};

static const char _jancy_lexer_from_state_actions[] = {
	0, 0, 0, 0, 3, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 3, 0
};

static const short _jancy_lexer_eof_trans[] = {
	1, 1, 7, 1, 0, 40, 41, 42, 
	41, 42, 41, 45, 46, 46, 48, 49, 
	1, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 64, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 1, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 1, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 64, 50, 50, 50, 1, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 64, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 50, 50, 50, 
	50, 50, 50, 50, 50, 0, 244
};

static const int jancy_lexer_start = 4;
static const int jancy_lexer_first_final = 4;
static const int jancy_lexer_error = -1;

static const int jancy_lexer_en_main = 4;
static const int jancy_lexer_en_comment = 221;


/* #line 169 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */


//.............................................................................

#define BLOCK_STATE_NONE	0
#define BLOCK_STATE_COMMENT 1

void JancyHighlighter::ragelInit()
{
	
/* #line 707 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
	{
	cs = jancy_lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

/* #line 179 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
}

void JancyHighlighter::ragelExec()
{
	
/* #line 713 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _jancy_lexer_actions + _jancy_lexer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
/* #line 1 "NONE" */
	{ts = p;}
	break;
/* #line 730 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
		}
	}

	_keys = _jancy_lexer_trans_keys + _jancy_lexer_key_offsets[cs];
	_trans = _jancy_lexer_index_offsets[cs];

	_klen = _jancy_lexer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _jancy_lexer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _jancy_lexer_indicies[_trans];
_eof_trans:
	cs = _jancy_lexer_trans_targs[_trans];

	if ( _jancy_lexer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _jancy_lexer_actions + _jancy_lexer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
/* #line 1 "NONE" */
	{te = p+1;}
	break;
	case 3:
/* #line 136 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 1;}
	break;
	case 4:
/* #line 140 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 2;}
	break;
	case 5:
/* #line 141 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 3;}
	break;
	case 6:
/* #line 142 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 4;}
	break;
	case 7:
/* #line 144 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 6;}
	break;
	case 8:
/* #line 152 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 10;}
	break;
	case 9:
/* #line 141 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 10:
/* #line 144 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 11:
/* #line 148 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); {cs = 221; goto _again;} }}
	break;
	case 12:
/* #line 150 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;}
	break;
	case 13:
/* #line 152 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{  }}
	break;
	case 14:
/* #line 136 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::blue); }}
	break;
	case 15:
/* #line 140 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{  }}
	break;
	case 16:
/* #line 141 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 17:
/* #line 142 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 18:
/* #line 143 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 19:
/* #line 144 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 20:
/* #line 146 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 21:
/* #line 150 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;}
	break;
	case 22:
/* #line 152 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{  }}
	break;
	case 23:
/* #line 142 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{{p = ((te))-1;}{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 24:
/* #line 1 "NONE" */
	{	switch( act ) {
	case 1:
	{{p = ((te))-1;} colorize(ts, te, Qt::blue); }
	break;
	case 2:
	{{p = ((te))-1;}  }
	break;
	case 3:
	{{p = ((te))-1;} colorize(ts, te, Qt::darkRed); }
	break;
	case 4:
	{{p = ((te))-1;} colorize(ts, te, Qt::darkRed); }
	break;
	case 6:
	{{p = ((te))-1;} colorize(ts, te, Qt::darkRed); }
	break;
	case 10:
	{{p = ((te))-1;}  }
	break;
	}
	}
	break;
	case 25:
/* #line 163 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 26:
/* #line 164 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 27:
/* #line 165 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); {cs = 4; goto _again;} }}
	break;
	case 28:
/* #line 164 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkGreen); }}
	break;
/* #line 896 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
		}
	}

_again:
	_acts = _jancy_lexer_actions + _jancy_lexer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
/* #line 1 "NONE" */
	{ts = 0;}
	break;
/* #line 907 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _jancy_lexer_eof_trans[cs] > 0 ) {
		_trans = _jancy_lexer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

/* #line 184 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
}

int JancyHighlighter::getRagelState(int blockState)
{
	switch (blockState)
	{
		case 1:
			return jancy_lexer_en_comment;
	}

	return jancy_lexer_en_main;
}

void JancyHighlighter::ragelExecPreEvent(int &ragelState)
{
	setCurrentBlockState(BLOCK_STATE_NONE);

	if (previousBlockState() == BLOCK_STATE_COMMENT)
		ragelState = jancy_lexer_en_comment;
}

void JancyHighlighter::ragelExecPostEvent(int ragelState)
{
	if (ragelState == jancy_lexer_en_comment)
		setCurrentBlockState(BLOCK_STATE_COMMENT);
}

//.............................................................................
