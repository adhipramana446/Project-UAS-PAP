#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enum jenis barang
typedef enum {
  JAS = 1,
  BAJU,
  CELANA,
  TAS,
  DOMPET
} JenisBarang;

// union untuk harga barang berdasarkan jenis
typedef union {
  int jas;
  int baju;
  int celana;
  int tas;
  int dompet;
} HargaBarang;

// struct untuk barang
typedef struct {
  JenisBarang *jenis;
  int *jumlah;
} Barang;

// struct untuk karyawan
typedef struct {
  char *nama;
  Barang *barang;
  int *totalgaji;
} Karyawan;

// fungsi untuk menginput data barang
Barang* inputbarang() {
  // alokasi memori struct barang dengan malloc
  Barang *barang = malloc(sizeof(Barang));
  if (barang == NULL) {
    exit(1);
  }

  // alokasi memori, malloc ke jenis dan jumlah barang (dalam struct barang)
  barang->jenis = malloc(sizeof(JenisBarang));
  barang->jumlah = malloc(sizeof(int));

  if (barang->jenis == NULL || barang->jumlah == NULL) {
    free(barang);
    exit(1);
  }

  // pilih jenis barang
  printf("Pilih jenis barang: \n");
  printf("1. Jas\n2. Baju\n3. Celana\n4. Tas\n5. Dompet\n");

  do {
    printf("Macukkan pilihan (1-5): ");
    scanf("%d", barang->jenis);
  } while (*barang->jenis < JAS || *barang->jenis > DOMPET);

  // masukkan jumlah
  do {
    printf("Masukkan jumlah barang: ");
    scanf("%d", barang->jumlah);
  } while (*barang->jumlah < 1);

  return barang;
}

// fungsi untuk hitung gaji
int hitunggaji(Barang *barang, HargaBarang *harga) {
  switch (*barang->jenis) {
    case JAS:
      return *barang->jumlah * harga->jas;
    case BAJU:
      return *barang->jumlah * harga->baju;
    case CELANA:
      return *barang->jumlah * harga->celana;
    case TAS:
      return *barang->jumlah * harga->tas;
    case DOMPET:
      return *barang->jumlah * harga->dompet;
    default: return 0;
  }
}

// fungsi membebaskan memori
void bebasmemori(Karyawan *karyawan) {
  free(karyawan->nama);
  free(karyawan->barang);
  free(karyawan->totalgaji);
  free(karyawan);
}

int main(){
  // alokasi memori untuk union harga barang
  HargaBarang *harga = malloc(sizeof(HargaBarang));
  if (harga == NULL) {
    return 1;
  }

  // inisialisasi harga barang
  harga->jas = 150000;
  harga->baju = 120000;
  harga->celana = 100000;
  harga->tas = 80000;
  harga->dompet = 70000;

  // alokasi memori untuk struct karyawan
  Karyawan *karyawan = malloc(sizeof(Karyawan));
  if (karyawan == NULL) {
    free(harga);
    return 1;
  }

  // alokasi memori, malloc untuk nama dan total gaji karyawan
  karyawan->nama = malloc(100 * sizeof(char));
  karyawan->totalgaji = malloc(sizeof(int));

  if (karyawan->nama == NULL || karyawan->totalgaji == NULL) {
    free(karyawan);
    free(harga);
    return 1;
  }

  // input nama karyawan
  printf("Nama Karyawan: ");
  scanf(" %s", karyawan->nama);

  // memanggil fungsi inputbarang
  karyawan->barang = inputbarang();

  // memanggil fungsi hitung gaji 
  *karyawan->totalgaji = hitunggaji(karyawan->barang, harga);

  // tampilkan output
  printf("\n--- Data Karyawan ---\n");
  printf("Nama Karyawan: %s\n", karyawan->nama);

  printf("Jenis barang yang dibuat: ");
  switch (*karyawan->barang->jenis) {
    case JAS:
      printf("Jas\n");
      break;
    case BAJU:
      printf("Baju\n");
      break;
    case CELANA:
      printf("Celana\n");
      break;
    case TAS:
      printf("Tas\n");
      break;
    case DOMPET:
      printf("Dompet\n");
      break;
  }

  printf("Jumlah barang yang dibuat: %d\n", *karyawan->barang->jumlah);
  printf("Total Gaji: Rp%d\n", *karyawan->totalgaji);

  // memanggil fungis bebasmemori
  bebasmemori(karyawan);
  free(harga);

  return 0;
}