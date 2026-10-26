from flask import Flask, render_template, request, redirect, url_for
from collections import deque

# Struktur Data Linked List: Yosua 
class GuestNode:
    def __init__(self, name, room):
        self.name = name
        self.room = room
        self.next = None

# Struktur Data Linked List
class GuestList:
    def __init__(self):
        self.head = None

    def add_guest(self, name, room):
        new_guest = GuestNode(name, room)
        if not self.head:
            self.head = new_guest
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_guest

    def remove_guest(self, name):
        current = self.head
        prev = None
        while current:
            if current.name == name:
                if prev:
                    prev.next = current.next
                else:
                    self.head = current.next
                return current.room
            prev = current
            current = current.next
        return None

    def list_guests(self):
        data = []
        current = self.head
        while current:
            data.append((current.name, current.room))
            current = current.next
        return data

# Sistem Hotel
class HotelSystem:
    def __init__(self, floors=3, rooms_per_floor=5):
        self.queue = deque()
        self.guest_list = GuestList()
        self.rooms = [[None for _ in range(rooms_per_floor)] for _ in range(floors)] # Array: Yeremia Christoper

# Queue: Khalifan Sadri
    def add_to_queue(self, name):
        self.queue.append(name)

    def check_in(self):
        if not self.queue:
            return None, "Tidak ada tamu dalam antrian."
        guest = self.queue.popleft() #Queue: Khalifan Sadri
        for i in range(len(self.rooms)):
            for j in range(len(self.rooms[0])):
                if self.rooms[i][j] is None:
                    room_number = f"{i+1}0{j+1}"
                    self.rooms[i][j] = guest
                    self.guest_list.add_guest(guest, room_number)
                    return guest, room_number
        return None, "Semua kamar penuh."

    def check_out_by_room(self, room_number):
        try:
            floor = int(room_number[0]) - 1
            col = int(room_number[2]) - 1
        except:
            return False, "Format kamar salah. Contoh: 101, 203, dst."

        if floor < 0 or floor >= len(self.rooms) or col < 0 or col >= len(self.rooms[0]):
            return False, "Nomor kamar tidak valid."

        guest_name = self.rooms[floor][col]
        if guest_name is None:
            return False, "Kamar sudah kosong."

        self.rooms[floor][col] = None
        self.guest_list.remove_guest(guest_name)
        return True, f"{guest_name} berhasil check-out dari kamar {room_number}."

    def cancel_checkin(self, room_number):
        try:
            floor = int(room_number[0]) - 1
            col = int(room_number[2]) - 1
        except:
            return False, "Format kamar salah. Contoh: 101, 203, dst."

        if floor < 0 or floor >= len(self.rooms) or col < 0 or col >= len(self.rooms[0]):
            return False, "Nomor kamar tidak valid."

        guest_name = self.rooms[floor][col]
        if guest_name is None:
            return False, "Kamar sudah kosong, tidak ada check-in yang bisa dibatalkan."

        self.rooms[floor][col] = None
        self.guest_list.remove_guest(guest_name)
        return True, f"Check-in tamu {guest_name} di kamar {room_number} berhasil dibatalkan."

    def get_room_status(self):
        status = []
        for i, floor in enumerate(self.rooms):
            for j, room in enumerate(floor):
                room_num = f"{i+1}0{j+1}"
                status.append((room_num, "Kosong" if room is None else f"Terisi oleh {room}"))
        return status

    def get_queue(self):
        return list(self.queue)
    
# Array Yeremia Christoper
    def clear_all_guests(self):
        self.guest_list = GuestList()
        for i in range(len(self.rooms)):
            for j in range(len(self.rooms[0])):
                self.rooms[i][j] = None


# Flask Setup
app = Flask(__name__)
hotel = HotelSystem()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/tambah', methods=['POST'])
def tambah():
    name = request.form['name']
    hotel.add_to_queue(name)
    return redirect(url_for('index'))

@app.route('/checkin')
def checkin():
    guest, result = hotel.check_in()
    if guest:
        return render_template('checkin.html', guest=guest, room=result)
    else:
        return render_template('checkinc.html')

@app.route('/checkout', methods=['POST'])
def checkout():
    room = request.form['room']
    success, message = hotel.check_out_by_room(room)
    return f"{message} <a href='/'>Kembali</a>"

@app.route('/batal', methods=['POST'])
def batal():
    room = request.form['room']
    success, message = hotel.cancel_checkin(room)
    return f"{message} <a href='/'>Kembali</a>"

@app.route('/status')
def status():
    kamar = hotel.get_room_status()
    tamu = hotel.guest_list.list_guests()
    return render_template('status.html', rooms=kamar, guests=tamu)

@app.route('/hapus_semua', methods=['POST'])
def hapus_semua():
    hotel.clear_all_guests()
    return redirect(url_for('status'))


@app.route('/antrian')
def antrian():
    antrean = hotel.get_queue()
    return render_template('antrian.html', queue=antrean)

if __name__ == '__main__':
    app.run(debug=True)
