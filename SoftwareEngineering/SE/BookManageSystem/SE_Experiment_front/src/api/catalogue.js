import request from '@/utils/request'

export function addToTemporary(data) {
  return request({
    url: '/catalogue/addTemporary',
    method: 'post',
    data
  }
  )
}

export function searchCheckList(data) {
  return request({
    url: '/check/queryOrder',
    method: 'post',
    data
  })
}

export function searchDonation(data) {
  return request({
    url: '/catalogue/queryDonation',
    method: 'post',
    data
  })
}

export function addBook(data) {
  return request({
    url: '/catalogue/addBook',
    method: 'post',
    data
  })
}

export function queryDamgage(data) {
  return request({
    url: '/damage/queryDamage',
    method: 'post',
    data
  })
}

export function addDamage(data) {
  return request({
    url: '/damage/addDamage',
    method: 'post',
    data
  })
}

export function updateDamage(data) {
  return request({
    url: '/damage/updateDamage',
    method: 'post',
    data
  })
}

export function deleteDamage(data) {
  return request({
    url: '/damage/deleteDamage',
    method: 'post',
    data
  })
}

export function queryTemporary(data) {
  return request({
    url: '/catalogue/queryTemporary',
    method: 'post',
    data
  })
}
