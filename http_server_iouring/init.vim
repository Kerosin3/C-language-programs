call plug#begin('~/.config/nvim/plugged')
Plug 'tyru/open-browser.vim' " opens url in browser
Plug 'http://github.com/tpope/vim-surround' " Surrounding ysw)
Plug 'https://github.com/preservim/nerdtree', { 'on': 'NERDTreeToggle' }
Plug 'https://github.com/ap/vim-css-color' " CSS Color Preview
Plug 'https://github.com/tpope/vim-commentary' " For Commenting gcc & gc
Plug 'https://github.com/vim-airline/vim-airline'
Plug 'https://github.com/ycm-core/YouCompleteMe'
Plug 'https://github.com/tpope/vim-fugitive'
Plug 'rakr/vim-one'
Plug 'sickill/vim-monokai'
Plug 'SirVer/ultisnips'
Plug 'honza/vim-snippets'
Plug 'ervandew/supertab'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'jiangmiao/auto-pairs'
Plug 'mg979/vim-visual-multi', {'branch': 'master'}
Plug 'https://github.com/cdelledonne/vim-cmake'
Plug 'Yggdroot/indentLine'
Plug 'pearofducks/ansible-vim'
Plug 'nanotech/jellybeans.vim'
Plug 'embark-theme/vim', { 'as': 'embark', 'branch': 'main' }
call plug#end()
"colorscheme monokai
"colorscheme jellybeans
set termguicolors
colorscheme embark
syntax enable
set clipboard=unnamedplus
set background=dark 
set nu!
set mouse=a
set title
set cursorline
set encoding=utf-8 " Important to YCM
map q :quit<CR> " for quit only type q on command mode
let g:ycm_key_list_select_completion = ['<C-n>', '<Down>']
let g:ycm_key_list_previous_completion = ['<C-p>', '<Up>']
let g:SuperTabDefaultCompletionType = '<C-n>'
let g:UltiSnipsExpandTrigger = "<tab>"
let g:UltiSnipsJumpForwardTrigger = "<tab>"
let g:UltiSnipsJumpBackwardTrigger = "<s-tab>"
let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
let g:ycm_language_server =
  \ [{
  \   'name': 'ccls',
  \   'cmdline': [ 'ccls' ],
  \   'filetypes': [ 'c', 'cpp', 'cc', 'h', 'hpp' ],
  \   'project_root_files': [ '.ccls-root', 'compile_commands.json' ]
 \ }]
let g:ycm_clangd_args=['--header-insertion=never']
set completeopt-=preview
" for save using Ctrl + s on command mode
" Need run this command: echo 'stty -ixon' >> ~/.bashrc && exec $SHELL
map <C-s> :write<CR>
nnoremap <leader>n :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTree<CR>
nnoremap <C-t> :NERDTreeToggle<CR>
nnoremap <C-f> :NERDTreeFind<CR>
nnoremap <C-Left> :tabprevious<CR>
nnoremap <C-Right> :tabnext<CR>
" <C-Enter>     Insert single / [count] newline.
nnoremap <C-CR> i<CR><Esc>
