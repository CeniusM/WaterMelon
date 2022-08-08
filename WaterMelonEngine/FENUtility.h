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
        0,0,0,0,0,0,0,0,0,0, // 59
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
            ' ', //32	space
            '!',//    33	exclamation mark
            '"',//	34	quotation mark
            '#',//	35	number sign
            '$',//	36	dollar sign
            '%',//  37	percent sign
            '&',//  38	ampersand
            '\'',//	39	apostrophe
            '(',//    40	left parenthesis
            ')',//	41	right parenthesis
            '*',//     42	asterisk
            '+',//     43	plus sign
            ',',//	44	comma
            '-',//     45	hyphen
            '.',//	46	period
            '/',//     47	slash
            '0',//	48	digit 0
            '1',//	49	digit 1
            '2',//	50	digit 2
            '3',//	51	digit 3
            '4',//	52	digit 4
            '5',//	53	digit 5
            '6',//	54	digit 6
            '7',//	55	digit 7
            '8',//	56	digit 8
            '9',//	57	digit 9
            ':',//	58	colon
            ';',//	59	semicolon
            '<',//     60	less - than
            '=',//     61	equals - to
            '>',//	62	greater - than
            '?',//     63	question mark
            '@',//	64	at sign
            'A',//	65	uppercase A
            'B',//	66	uppercase B
            'C',//	67	uppercase C
            'D',//	68	uppercase D
            'E',//	69	uppercase E
            'F',//	70	uppercase F
            'G',//	71	uppercase G
            'H',//	72	uppercase H
            'I',//	73	uppercase I
            'J',//	74	uppercase J
            'K',//	75	uppercase K
            'L',//	76	uppercase L
            'M',//	77	uppercase M
            'N',//	78	uppercase N
            'O',//	79	uppercase O
            'P',//	80	uppercase P
            'Q',//	81	uppercase Q
            'R',//	82	uppercase R
            'S',//	83	uppercase S
            'T',//	84	uppercase T
            'U',//	85	uppercase U
            'V',//	86	uppercase V
            'W',//	87	uppercase W
            'X',//	88	uppercase X
            'Y',//	89	uppercase Y
            'Z',//	90	uppercase Z
            '[',//    91	left square bracket
            '\\',//	92	backslash
            ']',//	93	right square bracket
            '^',//     94	caret
            '_',//	95	underscore
            '`',//	96	grave accent
            'a',//	97	lowercase a
            'b',//	98	lowercase b
            'c',//	99	lowercase c
            'd',//	100	lowercase d
            'e',//	101	lowercase e
            'f',//	102	lowercase f
            'g',//	103	lowercase g
            'h',//	104	lowercase h
            'i',//	105	lowercase i
            'j',//	106	lowercase j
            'k',//	107	lowercase k
            'l',//	108	lowercase l
            'm',//	109	lowercase m
            'n',//	110	lowercase n
            'o',//	111	lowercase o
            'p',//	112	lowercase p
            'q',//	113	lowercase q
            'r',//	114	lowercase r
            's',//	115	lowercase s
            't',//	116	lowercase t
            'u',//	117	lowercase u
            'v',//	118	lowercase v
            'w',//	119	lowercase w
            'x',//	120	lowercase x
            'y',//	121	lowercase y
            'z',//	122	lowercase z
            '{',//	123	left curly brace
            '|',//    124	vertical bar
            '}',//	125	right curly brace
            '~'//    126	tilde
    };
}