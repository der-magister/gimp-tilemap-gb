//
// lib_gbr_ops.h
//

#include "lib_gbr.h"

#ifndef LIB_GBR_OPS_FILE_HEADER
#define LIB_GBR_OPS_FILE_HEADER

int32_t gbr_pal_get_buf(uint8_t * dest_buf, gbr_record * p_gbr);
int32_t gbr_tile_get_buf(uint8_t * dest_buf, gbr_record * p_gbr, uint16_t tile_index);

int32_t gbr_pal_set_buf(uint8_t * src_buf, gbr_record * p_gbr, uint16_t num_colors);
int32_t gbr_tile_set_buf(uint8_t * src_buf, gbr_record * p_gbr, uint16_t tile_index);

int32_t gbr_tile_copy_to_image(image_data * p_image, gbr_record * p_gbr, uint16_t tile_index, uint16_t map_x, uint16_t map_y);

#endif // LIB_GBR_OPS_FILE_HEADER