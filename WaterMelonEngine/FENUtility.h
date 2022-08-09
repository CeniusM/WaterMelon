#pragma once

#include "Piece.h"

namespace FENUtility
{

    // input the peice char value and get its Piece Value
    constexpr char CharToInt[] =
    {
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0, // 59
        0, // 60
        0, // 61
        0, // 62
        0, // 63
        0, // 'A'
        Piece::WBishop, // 'B'
        0, // 'C'
        0, // 'D'
        0, // 'E'
        0, // 'F'
        0, // 'G'
        0, // 'H'
        0, // 'I'
        0, // 'J'
        Piece::WKing, // 'K'
        0, // 'L'
        0, // 'M'
        Piece::WKnight, // 'N'
        0, // 'O'
        Piece::WPawn, // 'P'
        Piece::WQueen, // 'Q'
        Piece::WRook, // 'R'
        0, // 'S'
        0, // 'T'
        0, // 'U'
        0, // 'V'
        0, // 'W'
        0, // 'X'
        0, // 'Y'
        0, // 'Z'
        0, // '['
        0, // '\'
        0, // ']'
        0, // '^'
        0, // '_'
        0, // '`'
        0, // 'a'
        Piece::BBishop, // 'b'
        0, // 'c'
        0, // 'd'
        0, // 'e'
        0, // 'f'
        0, // 'g'
        0, // 'h'
        0, // 'i'
        0, // 'j'
        Piece::BKing, // 'k'
        0, // 'l'
        0, // 'm'
        Piece::BKnight, // 'n'
        0, // 'o'
        Piece::BPawn, // 'p'
        Piece::BQueen, // 'q'
        Piece::BRook, // 'r'
        0, // 's'
        0, // 't'
        0, // 'u'
        0, // 'v'
        0, // 'w'
        0, // 'x'
        0, // 'y'
        0  // 'z'
	};

    // input the Piece Value and get its ascii representation
    constexpr char IntToChar[] =
    {
            0, //0
            0, //1
            0, //2
            0, //3
            0, //4
            0, //5
            0, //6
            0, //7
            0, //8
            'K', //9 WKing
            'P', //10 WPawn
            'N', //11 WKnight
            0, //12
            'B', //13 WBishop
            'R', //14 WRook
            'Q', //15 WQueen
            0, //16
            'k', //17 BKing
            'p', //18 BPawn
            'n', //19 BKnight
            0, //20
            'b', //21 BBishop
            'r', //22 BRook
            'q', //23 BQueen
            0, //24
            0, //25
            0, //26
            0, //27
            0, //28
            0, //29
            0, //30
            0, //31
            0, //32	space
            0,//    33	exclamation mark
            0,//	34	quotation mark
            0,//	35	number sign
            0,//	36	dollar sign
            0,//  37	percent sign
            0,//  38	ampersand
            0,//	39	apostrophe
            0,//    40	left parenthesis
            0,//	41	right parenthesis
            0,//     42	asterisk
            0,//     43	plus sign
            0,//	44	comma
            0,//     45	hyphen
            0,//	46	period
            0,//     47	slash
            0,//	48	digit 0
            0,//	49	digit 1
            0,//	50	digit 2
            0,//	51	digit 3
            0,//	52	digit 4
            0,//	53	digit 5
            0,//	54	digit 6
            0,//	55	digit 7
            0,//	56	digit 8
            0,//	57	digit 9
            0,//	58	colon
            0,//	59	semicolon
            0,//     60	less - than
            0,//     61	equals - to
            0,//	62	greater - than
            0,//     63	question mark
            0,//	64	at sign
            0,//	65	uppercase A
            0,//	66	uppercase B
            0,//	67	uppercase C
            0,//	68	uppercase D
            0,//	69	uppercase E
            0,//	70	uppercase F
            0,//	71	uppercase G
            0,//	72	uppercase H
            0,//	73	uppercase I
            0,//	74	uppercase J
            0,//	75	uppercase K
            0,//	76	uppercase L
            0,//	77	uppercase M
            0,//	78	uppercase N
            0,//	79	uppercase O
            0,//	80	uppercase P
            0,//	81	uppercase Q
            0,//	82	uppercase R
            0,//	83	uppercase S
            0,//	84	uppercase T
            0,//	85	uppercase U
            0,//	86	uppercase V
            0,//	87	uppercase W
            0,//	88	uppercase X
            0,//	89	uppercase Y
            0,//	90	uppercase Z
            0,//    91	left square bracket
            0,//	92	backslash
            0,//	93	right square bracket
            0,//     94	caret
            0,//	95	underscore
            0,//	96	grave accent
            0,//	97	lowercase a
            0,//	98	lowercase b
            0,//	99	lowercase c
            0,//	100	lowercase d
            0,//	101	lowercase e
            0,//	102	lowercase f
            0,//	103	lowercase g
            0,//	104	lowercase h
            0,//	105	lowercase i
            0,//	106	lowercase j
            0,//	107	lowercase k
            0,//	108	lowercase l
            0,//	109	lowercase m
            0,//	110	lowercase n
            0,//	111	lowercase o
            0,//	112	lowercase p
            0,//	113	lowercase q
            0,//	114	lowercase r
            0,//	115	lowercase s
            0,//	116	lowercase t
            0,//	117	lowercase u
            0,//	118	lowercase v
            0,//	119	lowercase w
            0,//	120	lowercase x
            0,//	121	lowercase y
            0,//	122	lowercase z
            0,//	123	left curly brace
            0,//    124	vertical bar
            0,//	125	right curly brace
            0//    126	tilde
    };
}