import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

/* Layout */
import Layout from '@/layout'

/**
 * Note: sub-menu only appear when route children.length >= 1
 * Detail see: https://panjiachen.github.io/vue-element-admin-site/guide/essentials/router-and-nav.html
 *
 * hidden: true                   if set true, item will not show in the sidebar(default is false)
 * alwaysShow: true               if set true, will always show the root menu
 *                                if not set alwaysShow, when item has more than one children route,
 *                                it will becomes nested mode, otherwise not show the root menu
 * redirect: noRedirect           if set noRedirect will no redirect in the breadcrumb
 * name:'router-name'             the name is used by <keep-alive> (must set!!!)
 * meta : {
    roles: ['admin','user']    control the page roles (you can set multiple roles)
    title: 'title'               the name show in sidebar and breadcrumb (recommend set)
    icon: 'svg-name'             the icon show in the sidebar
    breadcrumb: false            if set false, the item will hidden in breadcrumb(default is true)
    activeMenu: '/example/list'  if set path, the sidebar will highlight the path you set
  }
 */

/**
 * constantRoutes
 * a base page that does not have permission requirements
 * all roles can be accessed
 */
export const constantRoutes = [
  {
    path: '/login',
    component: () => import('@/views/login/index'),
    hidden: true
  },

  {
    path: '/404',
    component: () => import('@/views/error-page/404'),
    hidden: true
  },

  {
    path: '/401',
    component: () => import('@/views/error-page/401'),
    hidden: true
  },

  {
    path: '/',
    component: Layout,
    redirect: '/dashboard',
    children: [{
      path: 'dashboard',
      name: '主页',
      component: () => import('@/views/dashboard/index'),
      meta: {title: '主页', icon: 'dashboard'}
    }]
  }
]

export const asyncRoutes = [

  {
    path: '/search',
    component: Layout,
    name: '图书检索',
    redirect: '/search/search',
    meta: {title: '图书检索', icon: 'form', roles: ['user', 'admin']},
    children: [
      {
        path: 'message',
        name: '读者留言',
        component: () => import('@/views/search/message/index'),
        meta: {
          title: '读者留言',
          icon: '留言',
          roles: ['user']
        }
      },
      {
        path: 'notice',
        name: '通告模块',
        component: () => import('@/views/search/notice/index'),
        meta: {
          title: '通告模块',
          icon: '书',
          roles: ['user', 'admin']
        }
      },
      {
        path: 'search',
        name: '检索',
        component: () => import('@/views/search/search/index'),
        meta: {title: '检索', icon: '检索', roles: ['user']}
      },
      {
        path: 'notification',
        name: '新书通报',
        component: () => import('@/views/catalogue/notification/index'),
        meta: {title: '新书检索', icon: '书', roles: ['user']}
      },
    ]
  },

  {
    path: '/catalogue',
    component: Layout,
    name: '编目系统',
    redirect: '/catalogue/catalogue',
    meta: {title: '编目系统', icon: 'form', roles: ['admin']},
    children: [
      {
        path: 'catalogue',
        name: '编目模块',
        component: () => import('@/views/catalogue/catalogue/index'),
        meta: {title: '编目模块', icon: '文献编目', roles: ['admin']}
      },
      {
        path: 'reimbursement_cancellation',
        name: '报损与注销',
        component: () => import('@/views/catalogue/reimbursement_cancellation/index'),
        meta: {title: '报损与注销', icon: '报销', roles: ['admin']}
      }
    ]
  },

  {
    path: '/circulation',
    component: Layout,
    name: '流通系统',
    redirect: '/circulation/search',
    meta: {title: '流通系统', icon: 'form', roles: ['user']},
    children: [
      {
        path: 'borrow',
        name: '借书',
        meta: {title: '借书', icon: '实物借阅', roles: ['user']},
        component: () => import('@/views/circulation/borrow/index'),
      },
      {
        path: 'return',
        name: '还书',
        meta: {title: '还书', icon: '图书归还', roles: ['user']},
        component: () => import('@/views/circulation/return/index'),
      },
      {
        path: 'search',
        name: '查询',
        meta: {title: '借书记录', icon: '查询', roles: ['user']},
        component: () => import('@/views/circulation/search/index'),
      }
    ]
  },

  {
    path: '/interview',
    component: Layout,
    redirect: '/interview/check',
    name: '采访系统',
    meta: {title: '采访系统', icon: 'form', roles: ['admin', 'user']},
    children: [
      {
        path: 'check',
        name: '验收模块',
        component: () => import('@/views/interview/check/index'),
        meta: {title: '验收模块', icon: '验收', roles: ['admin']}
      },
      {
        path: 'list',
        name: '采访清单',
        component: () => import('@/views/interview/list/index'),
        meta: {title: '采访清单', icon: 'form', roles: ['admin', 'user']}
      },
      {
        path: 'order',
        name: '订单模块',
        hidden: true,
        component: () => import('@/views/interview/order/index'),
        meta: {title: '订单模块', icon: '订单', roles: ['admin']}
      },
      {
        path: 'refund',
        name: '退货模块',
        component: () => import('@/views/interview/refund/index'),
        meta: {title: '退货模块', icon: '退货', roles: ['admin']}
      }
    ]
  },

  {
    path: '/periodical',
    component: Layout,
    name: '期刊系统',
    redirect: '/periodical/search',
    meta: {title: '期刊系统', icon: 'form', roles: ['admin', 'user']},
    children: [
      {
        path: 'modify',
        name: '期刊管理',
        component: () => import('@/views/periodical/modify/index'),
        meta: {title: '期刊管理', icon: '修改', roles: ['admin']}
      },
      {
        path: 'search',
        name: '查找',
        component: () => import('@/views/periodical/search/index'),
        meta: {title: '期刊', icon: '查询', roles: ['user']}
      },
      {
        path: 'subscribe',
        name: '订阅',
        component: () => import('@/views/periodical/subscribe/index'),
        meta: {title: '我的订阅', icon: '订阅', roles: ['user']}
      }
    ]
  },

  {
    path: '/maintain',
    component: Layout,
    name: '维护子系统',
    redirect: '/maintain/maintain',
    meta: {title: '维护子系统', icon: 'form', roles: ['admin']},
    children: [
      {
        path: 'maintain',
        name: '图书维护',
        component: () => import('@/views/maintain/maintain/index'),
        meta: {title: '图书维护', icon: '维护', roles: ['admin']}
      },
      {
        path: 'press',
        name: '出版社',
        component: () => import('@/views/maintain/press/index'),
        meta: {title: '出版社', icon: '出版社', roles: ['admin']}
      },
      {
        path: 'user',
        name: '用户',
        component: () => import('@/views/maintain/user/index'),
        meta: {title: '用户', icon: '用户', roles: ['admin']}
      }
    ]
  },

  // 404 page must be placed at the end !!!
  {path: '*', redirect: '/404', hidden: true}
]

const createRouter = () => new Router({
  // mode: 'history', // require service support
  scrollBehavior: () => ({y: 0}),
  routes: constantRoutes
})

const router = createRouter()

// Detail see: https://github.com/vuejs/vue-router/issues/1234#issuecomment-357941465
export function resetRouter() {
  const newRouter = createRouter()
  router.matcher = newRouter.matcher // reset router
}

export default router
