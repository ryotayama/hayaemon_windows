#ifdef __cplusplus
extern "C" {
#endif

#ifndef NSFSDKAPI
#define NSFSDKAPI
#endif

typedef struct NSFSDK_TAG *HNSF;

HNSF NSFSDKAPI NSFSDK_Load(void *pData, unsigned uSize);
void NSFSDKAPI NSFSDK_SetSongNo(HNSF hnsf, unsigned uSongNo);
void NSFSDKAPI NSFSDK_SetFrequency(HNSF hnsf, unsigned freq);
void NSFSDKAPI NSFSDK_SetNosefartFilter(HNSF hnsf, unsigned filter);
void NSFSDKAPI NSFSDK_SetChannel(HNSF hnsf, unsigned ch);
void NSFSDKAPI NSFSDK_Reset(HNSF hnsf);
void NSFSDKAPI NSFSDK_Volume(HNSF hnsf, unsigned uVolume);
void NSFSDKAPI NSFSDK_Render(HNSF hnsf, void *bufp, unsigned buflen);
void NSFSDKAPI NSFSDK_GetFileInfo(char **p1, char **p2, char **p3, char **p4);
void NSFSDKAPI NSFSDK_Terminate(HNSF hnsf);

unsigned NSFSDKAPI NSFSDK_GetSongNo(HNSF hnsf);
unsigned NSFSDKAPI NSFSDK_GetSongStart(HNSF hnsf);
unsigned NSFSDKAPI NSFSDK_GetSongMax(HNSF hnsf);
unsigned NSFSDKAPI NSFSDK_GetChannel(HNSF hnsf);

#ifdef __cplusplus
}
#endif
