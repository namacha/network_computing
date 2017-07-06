"
"  ___      ___ ___  _____ ______   ________  ________     
"  \  /  / | \  \ \  \\\__\ \  \ \  \|\  \ \  \___|    
"  \ \  \/   \ \  \ \  \    \ \  \ \  \\  \\ \  \____  
"|\__\ \__/ /     _|\|__|     \|__|\|__|\|__|\|_______|
"                                                    
" 2011- .vimrc

syntax on

"filetype_key = '<c-z>'

set backup
set backupdir=$HOME/.vim-backup
let &=========================
" neobundle.vim
"#====================starting')
  set runtimepath+=~/.vim/bundle/neobundle.vim/
  cal============
"   NeoBundle, Repository
" =======================cache"
"NeoBundle "davidhalter/jedi-vim"
"NeoBundle "Yggdroot/in "Shougo/unite.vim"
NeoBundle "Shougo/vimproc.vim", {
    \ 'buiake -f make_unix.mak',
    \ },
\}

NeoBundle "tpope/vim-surrouneoBundle "majutsushi/tagbar"
NeoBundle "vim-scripts/spec.vim"
Ne"
NeoBundleLazy "Shougo/vimfiler"
NeoBundle "hynek/vim-python-peybeans.vim"
NeoBundle "sickill/vim-monokai"
NeoBundle "tomasr/moeoBundle "lervag/vimtex"


filetype plugin indent on

"swap semi                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ab> <C-P>

set nowrap
set nu
set hlsearch
"nmap <Esc><Esc> :noh<i PmenuSel ctermbg=1
hi PMenuSbar ctermbg=4


filetype plugin on setl smartindent cinwords=if,elif,else,for,while,try,except,finshiftwidth=4 "softtabstop=2


"run python code on vim
function! command! Exec call <SID>Exec() 
map <silent> <C-P> :call <SID>Exvate/tmp/*

let g:neocomplcache_enable_at_startup = 1
imap <C-k>lcache_snippets_expand)
set completeopt-=preview

let g:ref_alc_=========

filetype plugin indent on

set shiftwidth=2

" vim-largetFormat = 'pdf'
let g:Tex_CompileRule_dvi = 'platex --interaci'
let g:Tex_FormatDependency_pdf = 'dvi,pdf'
let g:Tex_ViewRule!
  autocmd FileType html compiler nu-validator
augroup END

"aucmd FileType scheme nnoremap <buffer> ,t :!gosh %<CR>
language Cb=
set noerrorbells

" PEP8
let g:flake8_ignore="E111,E228"

setc.ayu15@gmail.com.>"
"au FileType spec map <buffer> <LocalLeaderpec
let g:changelog_timeformat = "%Y-%m-%d %H:%M"
let g:changeloNewFile *.py 0r $HOME/.vim/template/python.txt

" scroll
imap jj                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                remap jj <Esc>

set backspace=indent,eol,start


" =============                                                                ================
set cursorline


" ============================heme monokai


" ======================
"   Plugin Settings
" ==g:vimfiler_safe_mode_by_default = 0


" ======================
"emap # X#
