import request_x from '@/utils/request_x'

export function searchJournal(data) {
  return request_x({
    url: '/search_journal',
    method: 'post',
    data
  })
}

export function subscribeJournal(data) {
  return request_x({
    url: '/subscribe_journal',
    method: 'post',
    data
  })
}

export function searchSubscribe(data) {
  return request_x({
    url: '/search_subscribe',
    method: 'post',
    data
  })
}

export function cancelSubscribe(data) {
  return request_x({
    url: '/cancel_subscribe',
    method: 'post',
    data
  })
}

export function updateJournal(data) {
  return request_x({
    url: '/modify_journal',
    method: 'post',
    data
  })
}

export function addJournal(data) {
  return request_x({
    url: '/add_journal',
    method: 'post',
    data
  })
}

export function deleteJournal(data) {
  return request_x({
    url: '/delete_journal',
    method: 'post',
    data
  })
}

