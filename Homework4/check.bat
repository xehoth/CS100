:loop
gen.exe > tmp.in
ex2_no.exe < tmp.in > std.out && main_no.exe < tmp.in > me.out
fc /N std.out me.out || pause
goto loop
