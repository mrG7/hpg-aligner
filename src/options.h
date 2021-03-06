#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * hpg-fastq.h
 *
 *  Created on: Aug 29, 2012
 *      Author: imedina
 */

#include <stdlib.h>
#include <string.h>

#include "argtable/argtable2.h"
#include "config/libconfig.h"
#include "commons/log.h"
#include "commons/system_utils.h"
#include "commons/file_utils.h"
#include "buffers.h"

//========================================================================

#define HPG_ALIGNER_BIN      "hpg-aligner"
#define HPG_ALIGNER_NAME     "HPG-Aligner"
#define HPG_ALIGNER_VERSION  "2.1.0-beta"
#define OUTPUT_FILENAME      "alignments"

//============================ DEFAULT VALUES ============================
#define DEFAULT_GPU_THREADS		32
#define DEFAULT_CPU_THREADS		1
#define DEFAULT_CAL_SEEKER_ERRORS	0
#define DEFAULT_MIN_SEED_PADDING_LEFT	5
#define DEFAULT_MIN_SEED_PADDING_RIGHT	5
#define DEFAULT_WRITE_BATCH_SIZE	500000
#define DEFAULT_NUM_CAL_SEEKERS		1
#define DEFAULT_REGION_THREADS		1
#define DEFAULT_NUM_SW_THREADS		1
#define DEFAULT_MIN_NUM_SEEDS_IN_CAL	-1
#define DEFAULT_MAX_INTRON_LENGTH	500000
#define DEFAULT_MIN_INTRON_LENGTH	40

#define DEFAULT_MIN_SCORE		60

#define DEFAULT_SW_MATCH		5.0f
#define DEFAULT_SW_MISMATCH		-4.0f
#define DEFAULT_SW_GAP_OPEN		10.0f
#define DEFAULT_SW_GAP_EXTEND		0.5f
#define DEFAULT_PAIR_MODE	        0
#define DEFAULT_PAIR_MIN_DISTANCE	200
#define DEFAULT_PAIR_MAX_DISTANCE	800
#define MINIMUM_BATCH_SIZE              10000
#define DEFAULT_FILTER_READ_MAPPINGS    500
#define DEFAULT_FILTER_SEED_MAPPINGS    500

//========================================================================

#define DEFAULT_DNA_READ_BATCH_SIZE     200000
#define DEFAULT_DNA_NUM_SEEDS	        20
#define DEFAULT_DNA_MIN_CAL_SIZE        20

//========================================================================

#define DEFAULT_RNA_READ_BATCH_SIZE     200000
#define DEFAULT_RNA_NUM_SEEDS	        20
#define DEFAULT_RNA_MIN_CAL_SIZE        20
#define DEFAULT_RNA_SEED_SIZE           16

//========================================================================

#define DEFAULT_NUCLEOTIDES             "ACGT"
#define DEFAULT_FILTER_READ_MAPPINGS_BS 100
#define DEFAULT_FILTER_SEED_MAPPINGS_BS 500

//========================================================================

#define NUM_OPTIONS			31
#define NUM_RNA_OPTIONS			 5
#define NUM_DNA_OPTIONS			 1

#define FASTQ_FORMAT 1
#define BAM_FORMAT   2
#define SAM_FORMAT   3

#define FORMAT_STR(f) (f == BAM_FORMAT ? "BAM" : (f == SAM_FORMAT ? "SAM" : "FastQ"))

typedef struct options {
  int version;
  int mode;
  int gzip;
  int bam_format;
  int realignment;
  int recalibration;
  unsigned char bwt_set;
  unsigned char reg_set;
  unsigned char cal_set;
  unsigned char sw_set;
  int min_intron_length;
  int num_gpu_threads;
  int num_cpu_threads;
  int min_cal_size; 
  int num_seeds; 
  int min_num_seeds_in_cal; 
  int seeds_max_distance;
  int min_seed_padding_right;
  int min_seed_padding_left;
  int batch_size;
  int write_size;
  int num_cal_seekers;
  int min_seed_size;
  int seed_size;
  int max_intron_length;
  int flank_length;
  int timming;
  int statistics;
  int input_format;
  int output_format;
  int rna_seq; 
  int help;
  int cal_seeker_errors;
  int pair_mode;
  int pair_min_distance;
  int pair_max_distance;
  int report_all;
  int report_n_best;
  int report_n_hits;
  int report_best;
  int report_only_paired;
  int workflow_enable;
  int log_level;
  int index_ratio;
  int filter_read_mappings;
  int filter_seed_mappings;
  int bs_index;
  int fast_mode;
  int set_bam_format;
  int adapter_length;
  int set_cal;
  double min_score;
  double match;
  double mismatch;
  double gap_open;
  double gap_extend;  
  char str_mode[32];
  char *prefix_name;
  char *in_filename;
  char *in_filename2;
  char *bwt_dirname;
  char *genome_filename;
  char *output_name;
  char *header_filename;
  char *transcriptome_filename;
  char *intron_filename;
  char *adapter;
  char *adapter_revcomp;
  char *cmdline;
  // new variables for bisulphite case
} options_t;

options_t *options_new(void);

void options_free(options_t *options);

void options_display(options_t *options);

void usage_cli(int mode);

void validate_options(options_t *options);

/**
 * @brief Initializes an global_options_t structure mandatory members.
 * @return A new global_options_t structure.
 *
 * Initializes the only mandatory member of a global_options_t, which is the output directory.
 */
void** argtable_options_new(int mode);


/**
 * @brief Free memory associated to a global_options_data_t structure.
 * @param options_data the structure to be freed
 *
 * Free memory associated to a global_options_data_t structure, including its text buffers.
 */
void argtable_options_free(void **argtable_options, int num_options);


/**
 * @brief Initializes an global_options_data_t structure mandatory members.
 * @return A new global_options_data_t structure.
 *
 * Initializes the only mandatory member of a global_options_data_t, which is the output directory.
 */
options_t *read_CLI_options(void **argtable_options, options_t *options);



/**
 * @brief Reads the configuration parameters of the application.
 * @param filename file the options data are read from
 * @param options_data options values (vcf filename, output directory...)
 * @return Zero if the configuration has been successfully read, non-zero otherwise
 *
 * Reads the basic configuration parameters of the application. If the configuration file can't be
 * read, these parameters should be provided via the command-line interface.
 */
int read_config_file(const char *filename, options_t *options);

void options_to_file(options_t *options, FILE *fd);

options_t *parse_options(int argc, char **argv);


void usage(void **argtable, int mode);
void display_version();

char *create_cmdline(int argc, char **argv);

void display_help(void **argtable, int mode);
void display_dna_help();
void display_rna_help();

void display_options(options_t *options, FILE *file);
void display_dna_options(options_t *options, FILE *file);
void display_rna_options(options_t *options, FILE *file);



#endif
