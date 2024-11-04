
# Tugas Besar 1 IF3070 Dasar Inteligensi Artifisial & IF3170 Inteligensi Artifisial  
### Pencarian Solusi Diagonal Magic Cube dengan Local Search

## Kelompok 15  
- **Ariel Herfrison** - 13522002  
- **Andhika Tantyo Anugrah** - 13522094  
- **Kristo Anugrah** - 13522024  
- **Chelvadinda** - 13522154    

---

## Daftar Isi
- [Deskripsi Persoalan](#deskripsi-persoalan)
- [Setup dan Cara Menjalankan Program](#setup-dan-cara-menjalankan-program)
- [Pembagian Tugas](#pembagian-tugas)

### Deskripsi Singkat Repository
Repository ini berisi implementasi dari tiga algoritma local search untuk menyelesaikan permasalahan Diagonal Magic Cube berukuran 5x5x5. Permasalahan ini bertujuan untuk menyusun angka-angka pada kubus agar memenuhi properti-properti tertentu, termasuk jumlah angka yang sama pada tiap baris, kolom, tiang, dan diagonal ruang. Algoritma yang diimplementasikan meliputi:
- **Hill-Climbing**
- **Simulated Annealing**
- **Genetic Algorithm**

---

### Cara Setup dan Menjalankan Program

1. **Persiapan**
   - Pastikan Anda memiliki compiler C++ (seperti `g++`) dan Python yang terinstall.
   - Install library Python yang diperlukan untuk visualisasi dengan perintah:
     ```bash
     pip install matplotlib
     ```

2. **Menjalankan Algoritma**
   - Compile kode yang ingin dijalankan. Misalnya, untuk Simulated Annealing:
     ```bash
     g++ annealing.cpp -o annealing
     ```
   - Jalankan program dengan perintah:
     ```bash
     ./annealing
     ```

### Pembagian Tugas

- **Ariel Herfrison (13522002)**: Implementasi dan Eksperimen Genetic Algorithm.
- **Andhika Tantyo Anugrah (13522094)**: Implementasi dan Eksperimen Hill-Climbing Algorithm.
- **Kristo Anugrah (13522024)**: Implementasi dan Eksperimen Simulated Annealing Algorithm.
- **Chelvadinda (13522154)**: Membuat laporan.

