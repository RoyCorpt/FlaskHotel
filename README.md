# 🏨 Manajemen Hotel

Aplikasi web sederhana untuk mengelola antrian tamu, check-in, dan check-out hotel. Dibangun dengan **Python (Flask)** dan menerapkan struktur data **Queue**, **Linked List**, dan **Array 2 Dimensi**.

## Fitur

- Menambahkan tamu ke antrian (FIFO)
- Memproses check-in: tamu pertama di antrian otomatis mendapat kamar kosong pertama
- Check-out berdasarkan nomor kamar
- Membatalkan check-in berdasarkan nomor kamar
- Melihat status seluruh kamar (kosong / terisi) dan daftar tamu
- Melihat daftar antrian tamu
- Menghapus semua data tamu yang sedang menginap

## Struktur Data yang Digunakan

| Struktur Data | Digunakan untuk | Lokasi |
| --- | --- | --- |
| `deque` (Queue) | Antrian tamu dengan prinsip FIFO | `HotelSystem.queue` |
| Linked List | Menyimpan daftar tamu yang sudah check-in | `GuestNode`, `GuestList` |
| List 2 Dimensi | Menyimpan status kamar per lantai | `HotelSystem.rooms` |

Hotel memiliki **3 lantai** dengan **5 kamar per lantai** (15 kamar). Nomor kamar berformat `<lantai>0<kamar>`:

```
Lantai 1: 101, 102, 103, 104, 105
Lantai 2: 201, 202, 203, 204, 205
Lantai 3: 301, 302, 303, 304, 305
```

## Struktur Proyek

```
.
├── app.py                  # Logika aplikasi dan routing Flask
├── static/
│   ├── style.css           # Style halaman beranda
│   ├── style-status.css    # Style halaman status kamar
│   ├── style-antrian.css   # Style halaman antrian
│   ├── checkin.css         # Style halaman check-in berhasil
│   └── checkinc.css        # Style halaman "tidak ada tamu"
└── templates/
    ├── index.html          # Beranda
    ├── status.html         # Status kamar dan daftar tamu
    ├── antrian.html        # Daftar antrian
    ├── checkin.html        # Hasil check-in berhasil
    └── checkinc.html       # Pesan jika antrian kosong
```

## Cara Menjalankan

### Prasyarat

- Python 3.8 atau lebih baru
- pip

### Langkah-langkah

1. Clone repositori ini:

   ```bash
   git clone https://github.com/<username>/<nama-repo>.git
   cd <nama-repo>
   ```

2. (Opsional) Buat dan aktifkan virtual environment:

   ```bash
   python -m venv venv

   # Linux / macOS
   source venv/bin/activate

   # Windows
   venv\Scripts\activate
   ```

3. Install Flask:

   ```bash
   pip install flask
   ```

4. Jalankan aplikasi:

   ```bash
   python app.py
   ```

5. Buka browser dan akses `http://127.0.0.1:5000`

> **Catatan:** Font Inter dimuat dari Google Fonts, jadi dibutuhkan koneksi internet agar tampilan font sesuai. Tanpa internet, browser akan memakai font bawaan.

## Cara Penggunaan

1. **Tambah tamu** → isi nama tamu di beranda, lalu klik *Tambah*.
2. **Proses check-in** → klik tautan *Proses Check-in*. Tamu terdepan di antrian akan mendapat kamar kosong pertama.
3. **Lihat status** → buka *Lihat Status Kamar & Tamu* untuk melihat kamar yang kosong dan terisi.
4. **Check-out** → masukkan nomor kamar (misalnya `101`), lalu klik *Check-out*.
5. **Batalkan check-in** → masukkan nomor kamar yang ingin dibatalkan, lalu klik *Batalkan*.
6. **Lihat antrian** → buka *Lihat Antrian* untuk melihat tamu yang menunggu.

## Daftar Route

| Method | Route | Fungsi |
| --- | --- | --- |
| GET | `/` | Halaman beranda |
| POST | `/tambah` | Menambah tamu ke antrian |
| GET | `/checkin` | Memproses check-in tamu berikutnya |
| POST | `/checkout` | Check-out berdasarkan nomor kamar |
| POST | `/batal` | Membatalkan check-in berdasarkan nomor kamar |
| GET | `/status` | Status kamar dan daftar tamu |
| POST | `/hapus_semua` | Menghapus semua data tamu |
| GET | `/antrian` | Daftar antrian tamu |

## Keterbatasan

- Data disimpan **di memori**, sehingga semua data hilang saat server dihentikan atau di-restart.
- Aplikasi berjalan dalam mode `debug=True`, hanya cocok untuk pengembangan dan belum untuk produksi.
- Penghapusan tamu dari linked list berdasarkan nama, sehingga tamu dengan nama yang sama dapat menimbulkan data yang tidak sesuai.
- Jika semua kamar penuh saat check-in diproses, tamu yang sedang diproses tidak dikembalikan ke antrian.

## Pengembangan Lebih Lanjut

- Menyimpan data ke database (misalnya SQLite)
- Mengubah `/checkin` menjadi route `POST`
- Validasi nomor kamar yang lebih ketat
- Tipe kamar dan harga
- Riwayat check-in dan check-out

## Lisensi

Tambahkan lisensi sesuai kebutuhan, misalnya [MIT](https://choosealicense.com/licenses/mit/).
