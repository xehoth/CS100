:loop
gen.exe > in.in
me.exe < in.in > me.out && std.exe < in.in > std.out
fc /N std.out me.out || pause
goto loop
