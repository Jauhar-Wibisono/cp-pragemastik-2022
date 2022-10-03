# Pra-Gemastik 15 Bidang Pemrograman - Problem Repository

## Repository Structure

Each problem (from A to M) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug   					| Problem Title             |
| ------------ | ---------------------------------- | --------------------------|
| A            | -							        | Closest Cell 2        	|
| B            | pragemastik-2022-jarak-benteng     | Jarak Benteng         	|
| C            | pragemastik-2022-taman-bilangan    | Taman Bilangan			|
| D            | -      							| Hitung Jajar Genjang 1 	|
| E            | -     								| Bermain Jenga 		    |
| F            | pragemastik-2022-perayaan-ketiga   | Perayaan Ketiga	        |
| G            | pragemastik-2022-sepasang-bintang 	| Sepasang Bintang			|
| H            | pragemastik-2022-tekan-satu        | Tekan Satu	            |
| I            | pragemastik-2022-menjadi-pustakawan| Menjadi Pustakawan        |
| J            | -          						| Maksimalkan XOR       	|
| K            | pragemastik-2022-kotak-pensil      | Kotak Pensil              |
| L            | pragemastik-2022-mengisi-pohon     | Mengisi Pohon	            |
| M            | pragemastik-2022-jembatan-layang   | Jembatan Layang           |

Unmentioned slugs are either warmup contest problems or unused problems.

In the problem folder, there should be the following files.

- `statement.tex`. The problem statement.
- `solution.cpp`. The official solution used to generate the outputs of the testcases.
- `scorer.cpp`. An optional validator used to validate contestants' output. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file.
  - The second parameter will be used as the filename of the judge's output file.
  - The third parameter will be used as the filename of the contestant's output file.
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.
- `spec.cpp`. A <a href="https://tcframe.toki.id/">tcframe</a> testcase generator code.
- `Makefile`. A makefile containing problem export preparation command.

## Solutions

Note that while there is only one official published solution, we have other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions