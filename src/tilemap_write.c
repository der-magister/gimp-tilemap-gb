/*=======================================================================
              TileMap & TileSet plugin for the GIMP
                 Copyright 2018 - Others & Nathan Osman (webp plugin base)

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
=======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <libgimp/gimp.h>

#include "tilemap_write.h"
#include "lib_tilemap.h"

#include "image_info.h"

#include "lib_rom_bin.h"

int write_tilemap(const gchar * filename, gint image_id, gint drawable_id, gint image_mode)
{
    int32_t status;
    int32_t export_format;

    GimpDrawable * drawable;
    GimpPixelRgn rgn;
    GimpParasite * img_parasite;

    image_data source_img;

    export_format = EXPORT_FORMAT_GBDK_C_SOURCE;

    FILE * file;

    status = 0; // Default to success

    // Get the drawable
    drawable = gimp_drawable_get(drawable_id);

    // Get the Bytes Per Pixel of the incoming app image
    source_img.bytes_per_pixel = (unsigned char)gimp_drawable_bpp(drawable_id);

// TODO: why is this showing "1" even when the source image has an alpha mask and transparency.
    // Is it due to the export functionality?
printf("write-tilemap.c: bytes per pixel= %d\n", source_img.bytes_per_pixel);
    // Abort if it's not 1 or 2 bytes per pixel
    // TODO: handle both 1 (no alpha) and 2 (has alpha) byte-per-pixel mode
    if (source_img.bytes_per_pixel > IMG_BITDEPTH_INDEXED_ALPHA) {
        return false;
    }

    // Get a pixel region from the layer
    gimp_pixel_rgn_init(&rgn,
                        drawable,
                        0, 0,
                        drawable->width,
                        drawable->height,
                        FALSE, FALSE);


    // Determine the array size for the app's image then allocate it
    source_img.width      = drawable->width;
    source_img.height     = drawable->height;
    source_img.size       = drawable->width * drawable->height * source_img.bytes_per_pixel;
    source_img.p_img_data = malloc(source_img.size);

    // Get the image data
    gimp_pixel_rgn_get_rect(&rgn,
                            source_img.p_img_data,
                            0, 0,
                            drawable->width,
                            drawable->height);


// TODO: EXPORT

    status = tilemap_export_process(&source_img);

    // TODO: Check colormap size and throw a warning if it's too large (4bpp vs 2bpp, etc)
//    if (status != 0) { };


    // Free the image data
    free(source_img.p_img_data);

    // Detach the drawable
    gimp_drawable_detach(drawable);


    if (status)
        status = tilemap_save(filename, export_format);

    tilemap_free_resources();

    return true;
}

