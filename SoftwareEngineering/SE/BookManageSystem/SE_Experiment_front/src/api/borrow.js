import request_x from '@/utils/request_x'

export function searchBorrow(data) {
  return request_x({
    url: '/search_borrow',
    method: 'post',
    data
  })
}

export function onlyBorrow(data) {
  return request_x({
    url: '/borrow_book',
    method: 'post',
    data
  })
}

export function onlyReturn(data) {
  return request_x({
    url: '/return_book',
    method: 'post',
    data
  })
}

export function searchUnReturn(data) {
  return request_x({
    url: '/search_unreturn',
    method: 'post',
    data
  })
}

