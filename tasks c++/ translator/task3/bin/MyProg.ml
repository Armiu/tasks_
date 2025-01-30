program
type
  student = record
    age: int,
    grade: int,
    woman: bool
  end;

var
  s: student,
  i, total: int;

begin
  total := 0;
  s.age := 20;
  s.grade := 4;
  read(s.woman);

  if (s.woman) then
    begin
        write(s.age + 1)
    end
  else
    write(s.woman);

  i := 10;

  while (i > 0) do
    begin
      write(s.age);
      write(s.grade);
      s.grade := s.grade * 2 + 1;
      total := total + s.age;
      i := i - 1
    end;

  write(total + 100)
end


