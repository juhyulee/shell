2장: 일반 규칙

프로젝트는 C 언어로 작성해야 합니다.
모든 코드는 Norm 규칙을 따라야 합니다. 보너스 파일/함수도 포함되며, Norm 오류가 발생하면 점수는 0점입니다.
코드에서 예상치 못한 종료(세그멘테이션 폴트, 버스 오류, 더블 프리 등) 가 발생해서는 안 됩니다.
이러한 오류가 발생하면 프로젝트는 비기능적인 것으로 간주되며 0점 처리됩니다.
동적 할당된 메모리는 적절히 해제해야 하며, 메모리 누수는 허용되지 않습니다.
프로젝트에는 Makefile을 제출해야 하며, 다음 규칙이 포함되어야 합니다.
$(NAME), all, clean, fclean, re
-Wall -Wextra -Werror 플래그를 사용하여 cc로 컴파일해야 하며, 불필요한 재링크(relink)를 하면 안 됩니다.
보너스를 구현할 경우, Makefile에 bonus 규칙을 추가해야 합니다.
libft를 사용할 경우, libft의 소스 코드와 Makefile을 libft 폴더에 포함해야 합니다.
테스트 프로그램을 작성하는 것이 권장되며, 제출할 필요는 없지만 방어 평가(defense)에서 유용할 수 있습니다.
Git 저장소에 제출해야 하며, Git 저장소의 코드만 평가됩니다.

3장: 필수 구현 사항

프로그램 이름: minishell
제출 파일: Makefile, *.h, *.c
외부 함수:
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free,
write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset,
kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror,
perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

Minishell은 다음 기능을 제공해야 합니다.
새로운 명령을 대기할 때 프롬프트를 표시해야 합니다.
명령어 히스토리 기능을 지원해야 합니다.
PATH 환경 변수를 활용하여 실행 파일을 검색 및 실행해야 합니다.
글로벌 변수 사용 제한:
단 하나의 전역 변수만 사용할 수 있으며, 신호(signal) 수신 상태만 저장할 수 있습니다.
전역 변수를 활용한 다른 데이터 접근은 금지됩니다.
특수 문자 처리
닫히지 않은 따옴표(', ")나 특정 특수 문자(\, ; 등)는 해석하지 않아야 합니다.
싱글 쿼트('): 해당 부분에서 메타문자를 해석하지 않아야 합니다.
더블 쿼트("): 메타문자를 해석하지 않지만, $ 기호는 예외적으로 해석해야 합니다.
리디렉션 기능
< : 입력 리디렉션
> : 출력 리디렉션
<< : 히어독(Heredoc) 기능 (지정된 종료 문자열을 만날 때까지 입력)
>> : 출력 리디렉션 (덧붙이기 모드)
파이프(|) 지원
한 명령의 출력을 다음 명령의 입력으로 전달해야 합니다.
환경 변수 처리
$변수명 형태로 입력하면 해당 환경 변수의 값을 출력해야 합니다.
최근 실행된 명령의 종료 상태 ($?) 표시
시그널 처리
Ctrl + C → 새 프롬프트를 표시
Ctrl + D → 셸 종료
Ctrl + \ → 아무 동작 없음
Bash와 동일한 기본 내장 명령어를 지원해야 합니다.
echo (-n 옵션 지원)
cd (절대 경로 및 상대 경로 지원)
pwd
export
unset
env
exit
readline() 함수 자체에서 발생하는 메모리 누수는 수정하지 않아도 됩니다.
하지만 개발자가 작성한 코드에서의 메모리 누수는 허용되지 않습니다.

Bash를 기준으로 기능을 구현해야 하며, 명세에 없는 기능은 구현하지 않아도 됩니다.
