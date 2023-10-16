
Repository is WIP, and currenty isn't buildable(not sure why).


Way that should work to run repository but don't:
  - Download visual studio. Add C++ developement in insteller
  - Set VCPKG_ROOT in env usualy in:
    - C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg
  - clone repo https://github.com/dremio/flightsql-odbc
  - run `.\build_win64.bat`

TODO:
Find way to replace UnionScalar::value in code:
  PR where UnionScalar::value disapeared
  https://github.com/apache/arrow/pull/13521/files#diff-0df9ec77ca57be897102ef78fc030c4b2fea9b161bab5719a4957bb57224ae9b

