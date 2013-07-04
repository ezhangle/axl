
/* #line 1 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
#include "pch.h"
#include "jancyhighlighter.h"
#include "moc_jancyhighlighter.cpp"

//.............................................................................


/* #line 2 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
static const char _jancy_lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 2, 2, 3, 2, 2, 
	4, 2, 2, 5, 2, 2, 6
};

static const short _jancy_lexer_key_offsets[] = {
	0, 3, 6, 12, 46, 49, 52, 53, 
	56, 57, 59, 60, 64, 66, 72, 79, 
	89, 97, 105, 113, 121, 129, 137, 145, 
	153, 161, 169, 177, 186, 194, 202, 212, 
	221, 229, 237, 245, 253, 261, 269, 277, 
	285, 293, 301, 309, 317, 325, 333, 341, 
	349, 361, 369, 377, 385, 393, 401, 409, 
	417, 425, 434, 442, 450, 458, 466, 474, 
	482, 491, 501, 509, 517, 525, 533, 541, 
	549, 557, 568, 576, 584, 592, 600, 608, 
	616, 624, 632, 640, 652, 660, 668, 676, 
	684, 692, 700, 708, 716, 724, 732, 740, 
	748, 757, 766, 774, 782, 790, 802, 810, 
	818, 826, 834, 842, 851, 859, 867, 875, 
	883, 891, 901, 909, 917, 925, 933, 941, 
	949, 957, 965, 973, 984, 992, 1000, 1008, 
	1017, 1025, 1033, 1041, 1049, 1057, 1065, 1073, 
	1081, 1089, 1097, 1105, 1113, 1121, 1132, 1140, 
	1148, 1156, 1164, 1172, 1180, 1189, 1197, 1205, 
	1213, 1221, 1230, 1239, 1247, 1255, 1263, 1271, 
	1279, 1287, 1295, 1303, 1311, 1319, 1327, 1335, 
	1344, 1352, 1360, 1368, 1376, 1384, 1392, 1403, 
	1413, 1421, 1429, 1437, 1445, 1455, 1464, 1472, 
	1480, 1488, 1496, 1504, 1512, 1520, 1530, 1539, 
	1548, 1556, 1564, 1572, 1580, 1589, 1597, 1607, 
	1616, 1625, 1633, 1641, 1649, 1657, 1665, 1675, 
	1683, 1691, 1699, 1707, 1715, 1723, 1731, 1740, 
	1748, 1756, 1764, 1773, 1775
};

static const char _jancy_lexer_trans_keys[] = {
	10, 34, 92, 10, 39, 92, 48, 57, 
	65, 70, 97, 102, 9, 10, 13, 32, 
	34, 39, 47, 48, 95, 97, 98, 99, 
	100, 101, 102, 103, 104, 105, 109, 110, 
	111, 112, 114, 115, 116, 117, 118, 119, 
	49, 57, 65, 90, 106, 122, 9, 13, 
	32, 10, 34, 92, 10, 10, 39, 92, 
	10, 42, 47, 10, 88, 120, 48, 57, 
	48, 57, 48, 57, 65, 70, 97, 102, 
	95, 48, 57, 65, 90, 97, 122, 95, 
	98, 108, 117, 48, 57, 65, 90, 97, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 99, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 101, 103, 48, 57, 65, 90, 
	97, 122, 95, 118, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 105, 111, 114, 48, 57, 
	65, 90, 97, 122, 95, 103, 110, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 100, 48, 
	57, 65, 90, 97, 122, 95, 105, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 100, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 98, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 107, 48, 
	57, 65, 90, 97, 122, 95, 97, 100, 
	104, 108, 111, 48, 57, 65, 90, 98, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 99, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 115, 116, 48, 57, 65, 90, 
	97, 122, 95, 116, 48, 57, 65, 90, 
	97, 122, 95, 114, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 105, 48, 57, 65, 90, 
	97, 122, 95, 110, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 101, 111, 48, 57, 65, 
	90, 97, 122, 95, 102, 108, 115, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 117, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 116, 48, 
	57, 65, 90, 97, 122, 95, 117, 48, 
	57, 65, 90, 97, 122, 95, 108, 110, 
	118, 120, 48, 57, 65, 90, 97, 122, 
	95, 117, 48, 57, 65, 90, 97, 122, 
	95, 109, 48, 57, 65, 90, 97, 122, 
	95, 99, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 110, 48, 57, 65, 90, 97, 122, 
	95, 116, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 110, 48, 57, 65, 90, 97, 122, 
	95, 100, 48, 57, 65, 90, 97, 122, 
	95, 97, 108, 111, 114, 117, 48, 57, 
	65, 90, 98, 122, 95, 108, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 110, 48, 57, 
	65, 90, 97, 122, 95, 99, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 111, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 112, 48, 57, 
	65, 90, 97, 122, 95, 102, 110, 48, 
	57, 65, 90, 97, 122, 95, 100, 116, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 95, 120, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	48, 57, 65, 90, 97, 122, 49, 51, 
	54, 56, 95, 112, 48, 57, 65, 90, 
	97, 122, 54, 95, 48, 57, 65, 90, 
	97, 122, 50, 95, 48, 57, 65, 90, 
	97, 122, 52, 95, 48, 57, 65, 90, 
	97, 122, 95, 116, 48, 57, 65, 90, 
	97, 122, 95, 117, 48, 57, 65, 90, 
	97, 122, 95, 108, 116, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 95, 105, 48, 57, 65, 
	90, 97, 122, 95, 99, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 115, 48, 57, 65, 
	90, 97, 122, 95, 97, 101, 117, 48, 
	57, 65, 90, 98, 122, 95, 109, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 115, 48, 
	57, 65, 90, 97, 122, 95, 112, 48, 
	57, 65, 90, 97, 122, 95, 97, 48, 
	57, 65, 90, 98, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 119, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 108, 48, 
	57, 65, 90, 97, 122, 95, 98, 110, 
	112, 118, 48, 57, 65, 90, 97, 122, 
	95, 106, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 99, 48, 57, 65, 90, 97, 122, 
	95, 101, 104, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 97, 48, 57, 65, 90, 98, 
	122, 95, 116, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 100, 48, 57, 65, 90, 97, 
	122, 95, 97, 111, 114, 117, 48, 57, 
	65, 90, 98, 122, 95, 99, 48, 57, 
	65, 90, 97, 122, 95, 115, 48, 57, 
	65, 90, 97, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 102, 48, 57, 
	65, 90, 97, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 120, 48, 57, 
	65, 90, 97, 122, 95, 101, 111, 48, 
	57, 65, 90, 97, 122, 95, 99, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 115, 48, 
	57, 65, 90, 97, 122, 95, 112, 116, 
	48, 57, 65, 90, 97, 122, 95, 101, 
	118, 48, 57, 65, 90, 97, 122, 95, 
	114, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	121, 48, 57, 65, 90, 97, 122, 95, 
	97, 48, 57, 65, 90, 98, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	99, 48, 57, 65, 90, 97, 122, 95, 
	116, 48, 57, 65, 90, 97, 122, 95, 
	98, 48, 57, 65, 90, 97, 122, 95, 
	108, 48, 57, 65, 90, 97, 122, 95, 
	105, 48, 57, 65, 90, 97, 122, 95, 
	101, 48, 57, 65, 90, 97, 122, 95, 
	97, 116, 48, 57, 65, 90, 98, 122, 
	95, 100, 48, 57, 65, 90, 97, 122, 
	95, 111, 48, 57, 65, 90, 97, 122, 
	95, 110, 48, 57, 65, 90, 97, 122, 
	95, 108, 48, 57, 65, 90, 97, 122, 
	95, 117, 48, 57, 65, 90, 97, 122, 
	95, 114, 48, 57, 65, 90, 97, 122, 
	95, 101, 105, 116, 119, 48, 57, 65, 
	90, 97, 122, 95, 103, 108, 122, 48, 
	57, 65, 90, 97, 121, 95, 110, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 111, 48, 
	57, 65, 90, 97, 122, 95, 102, 48, 
	57, 65, 90, 97, 122, 95, 97, 100, 
	114, 48, 57, 65, 90, 98, 122, 95, 
	99, 116, 48, 57, 65, 90, 97, 122, 
	95, 99, 48, 57, 65, 90, 97, 122, 
	95, 97, 48, 57, 65, 90, 98, 122, 
	95, 108, 48, 57, 65, 90, 97, 122, 
	95, 105, 48, 57, 65, 90, 97, 122, 
	95, 116, 48, 57, 65, 90, 97, 122, 
	95, 99, 48, 57, 65, 90, 97, 122, 
	95, 104, 48, 57, 65, 90, 97, 122, 
	95, 104, 114, 121, 48, 57, 65, 90, 
	97, 122, 95, 105, 114, 48, 57, 65, 
	90, 97, 122, 95, 110, 115, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 112, 48, 57, 
	65, 90, 97, 122, 95, 101, 48, 57, 
	65, 90, 97, 122, 95, 100, 111, 48, 
	57, 65, 90, 97, 122, 95, 101, 48, 
	57, 65, 90, 97, 122, 95, 104, 110, 
	115, 48, 57, 65, 90, 97, 122, 95, 
	105, 115, 48, 57, 65, 90, 97, 122, 
	95, 97, 105, 48, 57, 65, 90, 98, 
	122, 95, 102, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 105, 48, 57, 65, 90, 97, 
	122, 95, 110, 48, 57, 65, 90, 97, 
	122, 95, 103, 48, 57, 65, 90, 97, 
	122, 95, 97, 105, 111, 48, 57, 65, 
	90, 98, 122, 95, 114, 48, 57, 65, 
	90, 97, 122, 95, 105, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 114, 48, 57, 65, 
	90, 97, 122, 95, 116, 48, 57, 65, 
	90, 97, 122, 95, 117, 48, 57, 65, 
	90, 97, 122, 95, 97, 48, 57, 65, 
	90, 98, 122, 95, 105, 108, 48, 57, 
	65, 90, 97, 122, 95, 97, 48, 57, 
	65, 90, 98, 122, 95, 116, 48, 57, 
	65, 90, 97, 122, 95, 105, 48, 57, 
	65, 90, 97, 122, 95, 101, 104, 48, 
	57, 65, 90, 97, 122, 10, 42, 47, 
	0
};

static const char _jancy_lexer_single_lengths[] = {
	3, 3, 0, 28, 3, 3, 1, 3, 
	1, 2, 1, 2, 0, 0, 1, 4, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 3, 2, 2, 4, 3, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	6, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	3, 4, 2, 2, 2, 2, 2, 2, 
	2, 5, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 6, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	3, 3, 2, 2, 2, 6, 2, 2, 
	2, 2, 2, 3, 2, 2, 2, 2, 
	2, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 5, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 5, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 3, 3, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 5, 4, 
	2, 2, 2, 2, 4, 3, 2, 2, 
	2, 2, 2, 2, 2, 4, 3, 3, 
	2, 2, 2, 2, 3, 2, 4, 3, 
	3, 2, 2, 2, 2, 2, 4, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 3, 2, 1
};

static const char _jancy_lexer_range_lengths[] = {
	0, 0, 3, 3, 0, 0, 0, 0, 
	0, 0, 0, 1, 1, 3, 3, 3, 
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
	3, 3, 3, 0, 0
};

static const short _jancy_lexer_index_offsets[] = {
	0, 4, 8, 12, 44, 48, 52, 54, 
	58, 60, 63, 65, 69, 71, 75, 80, 
	88, 94, 100, 106, 112, 118, 124, 130, 
	136, 142, 148, 154, 161, 167, 173, 181, 
	188, 194, 200, 206, 212, 218, 224, 230, 
	236, 242, 248, 254, 260, 266, 272, 278, 
	284, 294, 300, 306, 312, 318, 324, 330, 
	336, 342, 349, 355, 361, 367, 373, 379, 
	385, 392, 400, 406, 412, 418, 424, 430, 
	436, 442, 451, 457, 463, 469, 475, 481, 
	487, 493, 499, 505, 515, 521, 527, 533, 
	539, 545, 551, 557, 563, 569, 575, 581, 
	587, 594, 601, 607, 613, 619, 629, 635, 
	641, 647, 653, 659, 666, 672, 678, 684, 
	690, 696, 704, 710, 716, 722, 728, 734, 
	740, 746, 752, 758, 767, 773, 779, 785, 
	792, 798, 804, 810, 816, 822, 828, 834, 
	840, 846, 852, 858, 864, 870, 879, 885, 
	891, 897, 903, 909, 915, 922, 928, 934, 
	940, 946, 953, 960, 966, 972, 978, 984, 
	990, 996, 1002, 1008, 1014, 1020, 1026, 1032, 
	1039, 1045, 1051, 1057, 1063, 1069, 1075, 1084, 
	1092, 1098, 1104, 1110, 1116, 1124, 1131, 1137, 
	1143, 1149, 1155, 1161, 1167, 1173, 1181, 1188, 
	1195, 1201, 1207, 1213, 1219, 1226, 1232, 1240, 
	1247, 1254, 1260, 1266, 1272, 1278, 1284, 1292, 
	1298, 1304, 1310, 1316, 1322, 1328, 1334, 1341, 
	1347, 1353, 1359, 1366, 1369
};

static const unsigned char _jancy_lexer_indicies[] = {
	2, 2, 3, 1, 2, 2, 5, 4, 
	7, 7, 7, 6, 9, 10, 9, 9, 
	11, 12, 13, 14, 16, 17, 18, 19, 
	20, 21, 22, 23, 24, 25, 26, 27, 
	28, 29, 30, 31, 32, 33, 34, 35, 
	15, 16, 16, 8, 9, 9, 9, 36, 
	2, 2, 3, 1, 38, 1, 2, 2, 
	5, 4, 38, 4, 39, 40, 37, 41, 
	40, 43, 43, 15, 42, 15, 42, 7, 
	7, 7, 44, 16, 16, 16, 16, 0, 
	16, 46, 47, 48, 16, 16, 16, 45, 
	16, 49, 16, 16, 16, 45, 16, 50, 
	16, 16, 16, 45, 16, 51, 16, 16, 
	16, 45, 16, 52, 16, 16, 16, 45, 
	16, 53, 16, 16, 16, 45, 16, 54, 
	16, 16, 16, 45, 16, 55, 16, 16, 
	16, 45, 16, 56, 16, 16, 16, 45, 
	16, 54, 16, 16, 16, 45, 16, 57, 
	16, 16, 16, 45, 16, 58, 16, 16, 
	16, 45, 16, 60, 23, 16, 16, 16, 
	59, 16, 54, 16, 16, 16, 45, 16, 
	53, 16, 16, 16, 45, 16, 61, 62, 
	63, 16, 16, 16, 45, 16, 64, 65, 
	16, 16, 16, 45, 16, 66, 16, 16, 
	16, 45, 16, 67, 16, 16, 16, 45, 
	16, 68, 16, 16, 16, 45, 16, 69, 
	16, 16, 16, 45, 16, 70, 16, 16, 
	16, 45, 16, 54, 16, 16, 16, 45, 
	16, 71, 16, 16, 16, 45, 16, 72, 
	16, 16, 16, 0, 16, 73, 16, 16, 
	16, 45, 16, 74, 16, 16, 16, 45, 
	16, 54, 16, 16, 16, 45, 16, 75, 
	16, 16, 16, 45, 16, 54, 16, 16, 
	16, 45, 16, 76, 16, 16, 16, 45, 
	16, 77, 16, 16, 16, 45, 16, 54, 
	16, 16, 16, 45, 16, 78, 79, 80, 
	81, 82, 16, 16, 16, 45, 16, 74, 
	16, 16, 16, 45, 16, 83, 16, 16, 
	16, 45, 16, 75, 16, 16, 16, 45, 
	16, 84, 16, 16, 16, 45, 16, 54, 
	16, 16, 16, 45, 16, 85, 16, 16, 
	16, 45, 16, 56, 16, 16, 16, 45, 
	16, 86, 16, 16, 16, 45, 16, 87, 
	88, 16, 16, 16, 45, 16, 89, 16, 
	16, 16, 45, 16, 90, 16, 16, 16, 
	0, 16, 52, 16, 16, 16, 45, 16, 
	91, 16, 16, 16, 45, 16, 92, 16, 
	16, 16, 45, 16, 74, 16, 16, 16, 
	45, 16, 93, 94, 16, 16, 16, 45, 
	16, 95, 96, 97, 16, 16, 16, 45, 
	16, 98, 16, 16, 16, 45, 16, 99, 
	16, 16, 16, 45, 16, 53, 16, 16, 
	16, 45, 16, 100, 16, 16, 16, 45, 
	16, 74, 16, 16, 16, 45, 16, 101, 
	16, 16, 16, 45, 16, 72, 16, 16, 
	16, 59, 16, 78, 102, 103, 104, 16, 
	16, 16, 45, 16, 105, 16, 16, 16, 
	45, 16, 106, 16, 16, 16, 45, 16, 
	54, 16, 16, 16, 0, 16, 107, 16, 
	16, 16, 45, 16, 53, 16, 16, 16, 
	45, 16, 108, 16, 16, 16, 45, 16, 
	109, 16, 16, 16, 45, 16, 110, 16, 
	16, 16, 45, 16, 54, 16, 16, 16, 
	45, 16, 111, 112, 84, 113, 114, 16, 
	16, 16, 45, 16, 78, 16, 16, 16, 
	45, 16, 115, 16, 16, 16, 45, 16, 
	53, 16, 16, 16, 45, 16, 108, 16, 
	16, 16, 45, 16, 116, 16, 16, 16, 
	45, 16, 117, 16, 16, 16, 45, 16, 
	118, 16, 16, 16, 45, 16, 119, 16, 
	16, 16, 45, 16, 70, 16, 16, 16, 
	45, 16, 120, 16, 16, 16, 45, 16, 
	121, 16, 16, 16, 45, 16, 54, 16, 
	16, 16, 45, 16, 54, 122, 16, 16, 
	16, 45, 16, 123, 124, 16, 16, 16, 
	45, 16, 125, 16, 16, 16, 45, 16, 
	126, 16, 16, 16, 45, 16, 110, 16, 
	16, 16, 45, 127, 128, 129, 54, 16, 
	130, 16, 16, 16, 59, 54, 16, 16, 
	16, 16, 45, 54, 16, 16, 16, 16, 
	45, 54, 16, 16, 16, 16, 45, 16, 
	84, 16, 16, 16, 45, 16, 131, 16, 
	16, 16, 45, 16, 132, 71, 16, 16, 
	16, 45, 16, 133, 16, 16, 16, 45, 
	16, 134, 16, 16, 16, 45, 16, 135, 
	16, 16, 16, 45, 16, 136, 16, 16, 
	16, 45, 16, 53, 16, 16, 16, 45, 
	16, 137, 138, 139, 16, 16, 16, 45, 
	16, 140, 16, 16, 16, 45, 16, 141, 
	16, 16, 16, 45, 16, 142, 16, 16, 
	16, 45, 16, 143, 16, 16, 16, 45, 
	16, 144, 16, 16, 16, 45, 16, 74, 
	16, 16, 16, 45, 16, 54, 16, 16, 
	16, 45, 16, 145, 16, 16, 16, 45, 
	16, 146, 16, 16, 16, 45, 16, 147, 
	148, 149, 150, 16, 16, 16, 45, 16, 
	151, 16, 16, 16, 45, 16, 52, 16, 
	16, 16, 45, 16, 152, 16, 16, 16, 
	45, 16, 54, 153, 16, 16, 16, 45, 
	16, 154, 16, 16, 16, 45, 16, 155, 
	16, 16, 16, 45, 16, 74, 16, 16, 
	16, 45, 16, 156, 16, 16, 16, 45, 
	16, 157, 16, 16, 16, 45, 16, 158, 
	16, 16, 16, 45, 16, 159, 16, 16, 
	16, 45, 16, 84, 16, 16, 16, 45, 
	16, 160, 16, 16, 16, 45, 16, 161, 
	16, 16, 16, 45, 16, 162, 16, 16, 
	16, 45, 16, 163, 16, 16, 16, 45, 
	16, 74, 16, 16, 16, 45, 16, 164, 
	165, 166, 167, 16, 16, 16, 45, 16, 
	77, 16, 16, 16, 45, 16, 168, 16, 
	16, 16, 45, 16, 169, 16, 16, 16, 
	45, 16, 170, 16, 16, 16, 45, 16, 
	171, 16, 16, 16, 45, 16, 54, 16, 
	16, 16, 45, 16, 172, 173, 16, 16, 
	16, 45, 16, 174, 16, 16, 16, 45, 
	16, 175, 16, 16, 16, 45, 16, 176, 
	16, 16, 16, 45, 16, 97, 16, 16, 
	16, 45, 16, 177, 178, 16, 16, 16, 
	45, 16, 179, 180, 16, 16, 16, 45, 
	16, 181, 16, 16, 16, 45, 16, 182, 
	16, 16, 16, 45, 16, 54, 16, 16, 
	16, 45, 16, 183, 16, 16, 16, 45, 
	16, 92, 16, 16, 16, 45, 16, 184, 
	16, 16, 16, 45, 16, 185, 16, 16, 
	16, 45, 16, 126, 16, 16, 16, 45, 
	16, 186, 16, 16, 16, 45, 16, 187, 
	16, 16, 16, 45, 16, 188, 16, 16, 
	16, 45, 16, 189, 16, 16, 16, 45, 
	16, 190, 191, 16, 16, 16, 45, 16, 
	192, 16, 16, 16, 45, 16, 193, 16, 
	16, 16, 45, 16, 194, 16, 16, 16, 
	45, 16, 182, 16, 16, 16, 45, 16, 
	195, 16, 16, 16, 45, 16, 70, 16, 
	16, 16, 45, 16, 53, 196, 197, 198, 
	16, 16, 16, 45, 16, 199, 103, 200, 
	16, 16, 16, 45, 16, 126, 16, 16, 
	16, 45, 16, 201, 16, 16, 16, 45, 
	16, 202, 16, 16, 16, 45, 16, 54, 
	16, 16, 16, 45, 16, 203, 204, 90, 
	16, 16, 16, 45, 16, 77, 187, 16, 
	16, 16, 45, 16, 205, 16, 16, 16, 
	45, 16, 206, 16, 16, 16, 45, 16, 
	75, 16, 16, 16, 45, 16, 207, 16, 
	16, 16, 45, 16, 208, 16, 16, 16, 
	45, 16, 209, 16, 16, 16, 45, 16, 
	54, 16, 16, 16, 45, 16, 210, 92, 
	211, 16, 16, 16, 45, 16, 212, 213, 
	16, 16, 16, 45, 16, 54, 54, 16, 
	16, 16, 45, 16, 214, 16, 16, 16, 
	45, 16, 110, 16, 16, 16, 45, 16, 
	215, 16, 16, 16, 45, 16, 216, 16, 
	16, 16, 45, 16, 217, 202, 16, 16, 
	16, 45, 16, 202, 16, 16, 16, 45, 
	16, 24, 218, 219, 16, 16, 16, 45, 
	16, 119, 220, 16, 16, 16, 45, 16, 
	221, 222, 16, 16, 16, 45, 16, 74, 
	16, 16, 16, 45, 16, 199, 16, 16, 
	16, 45, 16, 223, 16, 16, 16, 45, 
	16, 224, 16, 16, 16, 45, 16, 54, 
	16, 16, 16, 45, 16, 225, 226, 227, 
	16, 16, 16, 45, 16, 228, 16, 16, 
	16, 45, 16, 229, 16, 16, 16, 45, 
	16, 107, 16, 16, 16, 45, 16, 230, 
	16, 16, 16, 45, 16, 231, 16, 16, 
	16, 45, 16, 232, 16, 16, 16, 45, 
	16, 75, 16, 16, 16, 45, 16, 110, 
	233, 16, 16, 16, 45, 16, 234, 16, 
	16, 16, 45, 16, 235, 16, 16, 16, 
	45, 16, 73, 16, 16, 16, 45, 16, 
	76, 235, 16, 16, 16, 45, 237, 238, 
	236, 240, 239, 0
};

static const unsigned char _jancy_lexer_trans_targs[] = {
	3, 0, 3, 6, 1, 8, 3, 13, 
	3, 4, 3, 5, 7, 9, 11, 12, 
	14, 15, 30, 48, 64, 73, 83, 29, 
	93, 96, 106, 113, 123, 141, 166, 174, 
	189, 198, 206, 218, 3, 3, 3, 3, 
	10, 3, 3, 2, 3, 3, 16, 22, 
	25, 17, 18, 19, 20, 21, 14, 23, 
	24, 26, 27, 3, 28, 31, 43, 45, 
	32, 38, 33, 34, 35, 36, 37, 39, 
	40, 41, 42, 44, 46, 47, 49, 50, 
	52, 54, 56, 51, 53, 55, 57, 58, 
	61, 59, 60, 62, 63, 65, 72, 66, 
	69, 71, 67, 68, 70, 59, 74, 77, 
	79, 75, 76, 78, 80, 81, 82, 84, 
	85, 87, 88, 86, 89, 90, 91, 92, 
	94, 95, 97, 98, 101, 99, 100, 102, 
	103, 104, 105, 107, 108, 109, 110, 111, 
	112, 114, 120, 121, 115, 116, 117, 118, 
	119, 122, 39, 124, 126, 131, 136, 125, 
	127, 128, 129, 130, 132, 133, 134, 135, 
	137, 138, 139, 140, 142, 143, 148, 163, 
	144, 145, 146, 147, 149, 153, 150, 151, 
	152, 154, 160, 155, 158, 156, 157, 159, 
	161, 162, 164, 165, 76, 167, 168, 172, 
	169, 170, 171, 173, 175, 180, 185, 176, 
	177, 178, 179, 181, 182, 183, 184, 186, 
	187, 188, 190, 194, 191, 192, 193, 195, 
	196, 197, 199, 203, 200, 201, 202, 204, 
	205, 207, 210, 214, 208, 209, 211, 212, 
	213, 215, 216, 217, 219, 219, 220, 219, 
	219
};

static const char _jancy_lexer_trans_actions[] = {
	33, 0, 7, 49, 0, 49, 31, 0, 
	13, 0, 11, 52, 52, 0, 5, 0, 
	46, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 27, 29, 19, 9, 
	0, 25, 21, 0, 23, 17, 0, 0, 
	0, 0, 0, 0, 0, 0, 43, 0, 
	0, 0, 0, 15, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 46, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 43, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 46, 0, 0, 
	0, 0, 43, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 43, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 46, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 37, 35, 0, 41, 
	39
};

static const char _jancy_lexer_to_state_actions[] = {
	0, 0, 0, 1, 0, 0, 0, 0, 
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
	0, 0, 0, 1, 0
};

static const char _jancy_lexer_from_state_actions[] = {
	0, 0, 0, 3, 0, 0, 0, 0, 
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
	0, 0, 0, 3, 0
};

static const short _jancy_lexer_eof_trans[] = {
	1, 1, 7, 0, 37, 38, 39, 38, 
	39, 38, 42, 43, 43, 45, 1, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 60, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 1, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 1, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	60, 46, 46, 46, 1, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 60, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 46, 46, 46, 46, 46, 
	46, 46, 46, 0, 240
};

static const int jancy_lexer_start = 3;
static const int jancy_lexer_first_final = 3;
static const int jancy_lexer_error = -1;

static const int jancy_lexer_en_main = 3;
static const int jancy_lexer_en_comment = 219;


/* #line 168 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */


//.............................................................................

#define BLOCK_STATE_NONE	0
#define BLOCK_STATE_COMMENT 1

void JancyHighlighter::ragelInit()
{
	
/* #line 705 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
	{
	cs = jancy_lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

/* #line 178 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
}

void JancyHighlighter::ragelExec()
{
	
/* #line 711 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
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
/* #line 728 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
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
/* #line 151 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{act = 9;}
	break;
	case 7:
/* #line 141 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 8:
/* #line 147 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); {cs = 219; goto _again;} }}
	break;
	case 9:
/* #line 149 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;}
	break;
	case 10:
/* #line 151 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{  }}
	break;
	case 11:
/* #line 136 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::blue); }}
	break;
	case 12:
/* #line 140 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{  }}
	break;
	case 13:
/* #line 141 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 14:
/* #line 142 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 15:
/* #line 143 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 16:
/* #line 145 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 17:
/* #line 149 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;}
	break;
	case 18:
/* #line 151 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{  }}
	break;
	case 19:
/* #line 142 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{{p = ((te))-1;}{ colorize(ts, te, Qt::darkRed); }}
	break;
	case 20:
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
	case 9:
	{{p = ((te))-1;}  }
	break;
	}
	}
	break;
	case 21:
/* #line 162 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 22:
/* #line 163 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); }}
	break;
	case 23:
/* #line 164 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p+1;{ colorize(ts, te, Qt::darkGreen); {cs = 3; goto _again;} }}
	break;
	case 24:
/* #line 163 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
	{te = p;p--;{ colorize(ts, te, Qt::darkGreen); }}
	break;
/* #line 876 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
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
/* #line 887 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl.cpp" */
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

/* #line 183 "D:/Prj/Ninja/axl/src/tests/JncQtTest/jancyhighlighter.rl" */
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