#ifndef NXCI_CNMT_H_
#define NXCI_CNMT_H_

#include <stdint.h>
#include "nsp.h"
#include "settings.h"
#include "filepath.h"

typedef struct {
    char *type;
    char id[0x21];
    uint64_t size;
    char hash[0x41];		// SHA-256
    unsigned char keygeneration;
} cnmt_xml_content_t;

typedef struct {
    filepath_t filepath;
    char *title_id;
    char *patch_id;
    uint32_t title_version;
    char *type;
    char *digest;
    unsigned char keygen_min;
    uint64_t requiredsysversion;
    cnmt_xml_content_t *contents;
} cnmt_xml_ctx_t;

#pragma pack(push, 1)
typedef struct {
    uint64_t title_id;
    uint32_t title_version;
    uint8_t type;
    uint8_t _0xD;
    uint16_t content_entry_offset;
    uint16_t content_entry_count;
    uint16_t meta_entry_count;
    uint8_t _0x14[0xC];
    uint64_t patch_id;
    uint64_t min_version;
} cnmt_header_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    unsigned char hash[0x20];
    uint8_t ncaid[0x10];
    uint8_t size[0x06];
    uint8_t type;
    uint8_t _0x37;
} cnmt_content_record_t;
#pragma pack(pop)

typedef struct {
    uint64_t title_id;
    uint64_t patch_id;
    uint8_t type;
    uint8_t nca_count;
    uint32_t title_version;
    unsigned char digest[0x20];
    unsigned char keygen_min;
    uint64_t requiredsysversion;
    cnmt_content_record_t *cnmt_content_records;
    filepath_t meta_filepath;
} cnmt_ctx_t;

void cnmt_create_xml(cnmt_xml_ctx_t *cnmt_xml_ctx, cnmt_ctx_t *cnmt_ctx, nsp_ctx_t *nsp_ctx);

void cnmt_gamecard_process(nxci_ctx_t *tool, cnmt_xml_ctx_t *cnmt_xml_ctx, cnmt_ctx_t *cnmt_ctx, nsp_ctx_t *nsp_ctx);
void cnmt_download_process(nxci_ctx_t *tool, cnmt_xml_ctx_t *cnmt_xml_ctx, cnmt_ctx_t *cnmt_ctx, nsp_ctx_t *nsp_ctx);

char *cnmt_get_content_type(uint8_t type);
char *cnmt_get_title_type(cnmt_ctx_t *cnmt_ctx);

extern cnmt_ctx_t application_cnmt;
extern cnmt_ctx_t patch_cnmt;
extern cnmt_ctx_t addon_cnmt;
extern cnmt_xml_ctx_t application_cnmt_xml;
extern cnmt_xml_ctx_t patch_cnmt_xml;
extern cnmt_xml_ctx_t addon_cnmt_xml;

#endif
