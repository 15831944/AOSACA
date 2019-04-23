/*  MUIstd.h

  matrix management functions:
  manipulations on matrices of data type "ui"

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#if !defined( __MUISTD_H )
#define __MUISTD_H

#if defined( _WIN64 )
   #if !defined( __MUQSTD_H )
      #include <MUQstd.h>
   #endif
   #define MUI_matrix          MUQ_matrix
   #define MUI_matrix0         MUQ_matrix0
   #define MUI_matrix_dbg      MUQ_matrix_dbg
   #define MUI_matrix0_dbg     MUQ_matrix0_dbg
   #define MUI_Pelement        MUQ_Pelement
   #define MUI_getElement      MUQ_getElement
   #define MUI_setElement      MUQ_setElement
   #define MUI_element         MUQ_element
   #define MUI_equ0            MUQ_equ0
   #define MUI_equ1            MUQ_equ1
   #define MUI_random          MUQ_random
   #define MUI_outerprod       MUQ_outerprod
   #define MUI_Row_equ0        MUQ_Row_equ0
   #define MUI_Col_equ0        MUQ_Col_equ0
   #define MUI_Dia_equ0        MUQ_Dia_equ0
   #define MUI_Row_equC        MUQ_Row_equC
   #define MUI_Col_equC        MUQ_Col_equC
   #define MUI_Dia_equC        MUQ_Dia_equC
   #define MUI_Row_equV        MUQ_Row_equV
   #define MUI_Col_equV        MUQ_Col_equV
   #define MUI_Dia_equV        MUQ_Dia_equV
   #define MUI_Trd_equM        MUQ_Trd_equM
   #define MUI_Trd_extract     MUQ_Trd_extract
   #define MUI_equM            MUQ_equM
   #define MUI_UequL           MUQ_UequL
   #define MUI_LequU           MUQ_LequU
   #define M_UBtoUI            M_UBtoUQ
   #define M_UStoUI            M_UStoUQ
   #define M_UtoUI             M_UtoUQ
   #define M_ULtoUI            M_ULtoUQ
   #define M_UQtoUI            MUQ_equM
   #define M_UItoUB            M_UQtoUB
   #define M_UItoUS            M_UQtoUS
   #define M_UItoU             M_UQtoU
   #define M_UItoUL            M_UQtoUL
   #define M_UItoUQ            MUQ_equM
   #define M_UItoF             M_UQtoF
   #define M_UItoD             M_UQtoD
   #define M_UItoE             M_UQtoE
   #define MUI_submatrix       MUQ_submatrix
   #define MUI_submatrix_equM  MUQ_submatrix_equM
   #define MUI_equMblock       MUQ_equMblock
   #define MUI_block_equM      MUQ_block_equM
   #define MUI_equMblockT      MUQ_equMblockT
   #define MUI_block_equMT     MUQ_block_equMT
   #define MUI_Row_extract     MUQ_Row_extract
   #define MUI_Col_extract     MUQ_Col_extract
   #define MUI_Dia_extract     MUQ_Dia_extract
   #define MUI_Row_delete      MUQ_Row_delete
   #define MUI_Col_delete      MUQ_Col_delete
   #define MUI_Row_insert      MUQ_Row_insert
   #define MUI_Col_insert      MUQ_Col_insert
   #define MUI_Rows_max        MUQ_Rows_max
   #define MUI_Cols_max        MUQ_Cols_max
   #define MUI_Dia_max         MUQ_Dia_max
   #define MUI_Rows_min        MUQ_Rows_min
   #define MUI_Cols_min        MUQ_Cols_min
   #define MUI_Dia_min         MUQ_Dia_min
   #define MUI_Rows_rotate     MUQ_Rows_rotate
   #define MUI_Cols_rotate     MUQ_Cols_rotate
   #define MUI_Rows_rotate_buf MUQ_Rows_rotate_buf
   #define MUI_Cols_rotate_buf MUQ_Cols_rotate_buf
   #define MUI_Rows_reflect    MUQ_Rows_reflect
   #define MUI_Cols_reflect    MUQ_Cols_reflect
   #define MUI_Rows_rev        MUQ_Rows_rev
   #define MUI_Cols_rev        MUQ_Cols_rev
   #define MUI_Rows_exchange   MUQ_Rows_exchange
   #define MUI_Cols_exchange   MUQ_Cols_exchange
   #define MUI_transpose       MUQ_transpose
   #define MUI_rotate90        MUQ_rotate90
   #define MUI_rotate180       MUQ_rotate180
   #define MUI_rotate270       MUQ_rotate270
   #define MUI_write           MUQ_write
   #define MUI_read            MUQ_read
   #define MUI_setWriteFormat  MUQ_setWriteFormat
   #define MUI_setWriteSeparate MUQ_setWriteSeparate
   #define MUI_store           MUQ_store
   #define MUI_recall          MUQ_recall

   #define MUIPelement        MUQPelement
   #define MUIgetElement      MUQgetElement
   #define MUIsetElement      MUQsetElement
   #define MUIelement         MUQelement
   #define MUIequ0            MUQequ0
   #define MUIequ1            MUQequ1
   #define MUIrandom          MUQrandom
   #define MUIouterprod       MUQouterprod
   #define MUIRow_equ0        MUQRow_equ0
   #define MUICol_equ0        MUQCol_equ0
   #define MUIDia_equ0        MUQDia_equ0
   #define MUIRow_equC        MUQRow_equC
   #define MUICol_equC        MUQCol_equC
   #define MUIDia_equC        MUQDia_equC
   #define MUIRow_equV        MUQRow_equV
   #define MUICol_equV        MUQCol_equV
   #define MUIDia_equV        MUQDia_equV
   #define MUITrd_equM        MUQTrd_equM
   #define MUITrd_extract     MUQTrd_extract
   #define MUIequM            MUQequM
   #define MUIUequL           MUQUequL
   #define MUILequU           MUQLequU
   #define MUBtoUI            MUBtoUQ
   #define MUStoUI            MUStoUQ
   #define MUtoUI             MUtoUQ
   #define MULtoUI            MULtoUQ
   #define MUQtoUI            MUQequM
   #define MUItoUB            MUQtoUB
   #define MUItoUS            MUQtoUS
   #define MUItoU             MUQtoU
   #define MUItoUL            MUQtoUL
   #define MUItoUQ            MUQequM
   #define MUItoF             MUQtoF
   #define MUItoD             MUQtoD
   #define MUItoE             MUQtoE
   #define MUIsubmatrix       MUQsubmatrix
   #define MUIsubmatrix_equM  MUQsubmatrix_equM
   #define MUIequMblock       MUQequMblock
   #define MUIblock_equM      MUQblock_equM
   #define MUIequMblockT      MUQequMblockT
   #define MUIblock_equMT     MUQblock_equMT
   #define MUIRow_extract     MUQRow_extract
   #define MUICol_extract     MUQCol_extract
   #define MUIDia_extract     MUQDia_extract
   #define MUIRow_delete      MUQRow_delete
   #define MUICol_delete      MUQCol_delete
   #define MUIRow_insert      MUQRow_insert
   #define MUICol_insert      MUQCol_insert
   #define MUIRows_max        MUQRows_max
   #define MUICols_max        MUQCols_max
   #define MUIDia_max         MUQDia_max
   #define MUIRows_min        MUQRows_min
   #define MUICols_min        MUQCols_min
   #define MUIDia_min         MUQDia_min
   #define MUIRows_rotate     MUQRows_rotate
   #define MUICols_rotate     MUQCols_rotate
   #define MUIRows_rotate_buf MUQRows_rotate_buf
   #define MUICols_rotate_buf MUQCols_rotate_buf
   #define MUIRows_reflect    MUQRows_reflect
   #define MUICols_reflect    MUQCols_reflect
   #define MUIRows_rev        MUQRows_rev
   #define MUICols_rev        MUQCols_rev
   #define MUIRows_exchange   MUQRows_exchange
   #define MUICols_exchange   MUQCols_exchange
   #define MUItranspose       MUQtranspose
   #define MUIrotate90        MUQrotate90
   #define MUIrotate180       MUQrotate180
   #define MUIrotate270       MUQrotate270
   #define MUIwrite           MUQwrite
   #define MUIread            MUQread
   #define MUIsetWriteFormat  MUQsetWriteFormat
   #define MUIsetWriteSeparate MUQsetWriteSeparate
   #define MUIstore           MUQstore
   #define MUIrecall          MUQrecall
#else   /* Win32 only  */
   #if !defined( __MUSTD_H )
      #include <MUstd.h>
   #endif
   #define MUI_matrix          MU_matrix
   #define MUI_matrix0         MU_matrix0
   #define MUI_matrix_dbg      MU_matrix_dbg
   #define MUI_matrix0_dbg     MU_matrix0_dbg
   #define MUI_Pelement        MU_Pelement
   #define MUI_element         MU_element
   #define MUI_getElement      MU_getElement
   #define MUI_setElement      MU_setElement
   #define MUI_equ0            MU_equ0
   #define MUI_equ1            MU_equ1
   #define MUI_random          MU_random
   #define MUI_outerprod       MU_outerprod
   #define MUI_Row_equ0        MU_Row_equ0
   #define MUI_Col_equ0        MU_Col_equ0
   #define MUI_Dia_equ0        MU_Dia_equ0
   #define MUI_Row_equC        MU_Row_equC
   #define MUI_Col_equC        MU_Col_equC
   #define MUI_Dia_equC        MU_Dia_equC
   #define MUI_Row_equV        MU_Row_equV
   #define MUI_Col_equV        MU_Col_equV
   #define MUI_Dia_equV        MU_Dia_equV
   #define MUI_Trd_equM        MU_Trd_equM
   #define MUI_Trd_extract     MU_Trd_extract
   #define MUI_equM            MU_equM
   #define MUI_UequL           MU_UequL
   #define MUI_LequU           MU_LequU
   #define M_UBtoUI            M_UBtoU
   #define M_UStoUI            M_UStoU
   #define M_UtoUI             M_UtoU
   #define M_ULtoUI            MU_equM
   #define M_UItoUB            M_UtoUB
   #define M_UItoUS            M_UtoUS
   #define M_UItoUL            M_UtoUL
   #define M_UItoU             MU_equM
   #define M_UItoF             M_UtoF
   #define M_UItoD             M_UtoD
   #define M_UItoE             M_UtoE
   #define MUI_submatrix       MU_submatrix
   #define MUI_submatrix_equM  MU_submatrix_equM
   #define MUI_equMblock       MU_equMblock
   #define MUI_block_equM      MU_block_equM
   #define MUI_equMblockT      MU_equMblockT
   #define MUI_block_equMT     MU_block_equMT
   #define MUI_Row_extract     MU_Row_extract
   #define MUI_Col_extract     MU_Col_extract
   #define MUI_Dia_extract     MU_Dia_extract
   #define MUI_Row_delete      MU_Row_delete
   #define MUI_Col_delete      MU_Col_delete
   #define MUI_Row_insert      MU_Row_insert
   #define MUI_Col_insert      MU_Col_insert
   #define MUI_Rows_max        MU_Rows_max
   #define MUI_Cols_max        MU_Cols_max
   #define MUI_Dia_max         MU_Dia_max
   #define MUI_Rows_min        MU_Rows_min
   #define MUI_Cols_min        MU_Cols_min
   #define MUI_Dia_min         MU_Dia_min
   #define MUI_Rows_rotate     MU_Rows_rotate
   #define MUI_Cols_rotate     MU_Cols_rotate
   #define MUI_Rows_rotate_buf MU_Rows_rotate_buf
   #define MUI_Cols_rotate_buf MU_Cols_rotate_buf
   #define MUI_Rows_reflect    MU_Rows_reflect
   #define MUI_Cols_reflect    MU_Cols_reflect
   #define MUI_Rows_rev        MU_Rows_rev
   #define MUI_Cols_rev        MU_Cols_rev
   #define MUI_Rows_exchange   MU_Rows_exchange
   #define MUI_Cols_exchange   MU_Cols_exchange
   #define MUI_transpose       MU_transpose
   #define MUI_rotate90        MU_rotate90
   #define MUI_rotate180       MU_rotate180
   #define MUI_rotate270       MU_rotate270
   #define MUI_write           MU_write
   #define MUI_read            MU_read
   #define MUI_setWriteFormat  MU_setWriteFormat
   #define MUI_setWriteSeparate MU_setWriteSeparate
   #define MUI_store           MU_store
   #define MUI_recall          MU_recall

   #define MUIPelement        MUPelement
   #define MUIelement         MUelement
   #define MUIgetElement      MUgetElement
   #define MUIsetElement      MUsetElement
   #define MUIequ0            MUequ0
   #define MUIequ1            MUequ1
   #define MUIrandom          MUrandom
   #define MUIouterprod       MUouterprod
   #define MUIRow_equ0        MURow_equ0
   #define MUICol_equ0        MUCol_equ0
   #define MUIDia_equ0        MUDia_equ0
   #define MUIRow_equC        MURow_equC
   #define MUICol_equC        MUCol_equC
   #define MUIDia_equC        MUDia_equC
   #define MUIRow_equV        MURow_equV
   #define MUICol_equV        MUCol_equV
   #define MUIDia_equV        MUDia_equV
   #define MUITrd_equM        MUTrd_equM
   #define MUITrd_extract     MUTrd_extract
   #define MUIequM            MUequM
   #define MUIUequL           MUUequL
   #define MUILequU           MULequU
   #define MUBtoUI            MUBtoU
   #define MUStoUI            MUStoU
   #define MUtoUI             MUtoU
   #define MULtoUI            MUequM
   #define MUItoUB            MUtoUB
   #define MUItoUS            MUtoUS
   #define MUItoUL            MUtoUL
   #define MUItoU             MUequM
   #define MUItoF             MUtoF
   #define MUItoD             MUtoD
   #define MUItoE             MUtoE
   #define MUIsubmatrix       MUsubmatrix
   #define MUIsubmatrix_equM  MUsubmatrix_equM
   #define MUIequMblock       MUequMblock
   #define MUIblock_equM      MUblock_equM
   #define MUIequMblockT      MUequMblockT
   #define MUIblock_equMT     MUblock_equMT
   #define MUIRow_extract     MURow_extract
   #define MUICol_extract     MUCol_extract
   #define MUIDia_extract     MUDia_extract
   #define MUIRow_delete      MURow_delete
   #define MUICol_delete      MUCol_delete
   #define MUIRow_insert      MURow_insert
   #define MUICol_insert      MUCol_insert
   #define MUIRows_max        MURows_max
   #define MUICols_max        MUCols_max
   #define MUIDia_max         MUDia_max
   #define MUIRows_min        MURows_min
   #define MUICols_min        MUCols_min
   #define MUIDia_min         MUDia_min
   #define MUIRows_rotate     MURows_rotate
   #define MUICols_rotate     MUCols_rotate
   #define MUIRows_rotate_buf MURows_rotate_buf
   #define MUICols_rotate_buf MUCols_rotate_buf
   #define MUIRows_reflect    MURows_reflect
   #define MUICols_reflect    MUCols_reflect
   #define MUIRows_rev        MURows_rev
   #define MUICols_rev        MUCols_rev
   #define MUIRows_exchange   MURows_exchange
   #define MUICols_exchange   MUCols_exchange
   #define MUItranspose       MUtranspose
   #define MUIrotate90        MUrotate90
   #define MUIrotate180       MUrotate180
   #define MUIrotate270       MUrotate270
   #define MUIwrite           MUwrite
   #define MUIread            MUread
   #define MUIsetWriteFormat  MUsetWriteFormat
   #define MUIsetWriteSeparate MUsetWriteSeparate
   #define MUIstore           MUstore
   #define MUIrecall          MUrecall
#endif  /*  Win64 or Win32 */
#endif  /*  __MUISTD_H  */
