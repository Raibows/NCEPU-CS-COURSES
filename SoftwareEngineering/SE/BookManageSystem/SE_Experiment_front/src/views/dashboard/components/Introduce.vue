<template>
  <el-card :body-style="{ padding: '0px' }">
    <img src="https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1592277892252&di=91e1432f25b2843598ed9db21d4120a2&imgtype=0&src=http%3A%2F%2Fimg0.imgtn.bdimg.com%2Fit%2Fu%3D1740893275%2C1826320088%26fm%3D214%26gp%3D0.jpg" class="image">
    <el-avatar :size="80" :src="currentUrl" style="margin-inline-start: 35%;margin-block-start: -60%"></el-avatar>
    <div style="padding: 14px;">
      <span>{{this.$store.getters.name}}</span>
      <div class="bottom clearfix">
        <time class="time">{{ this.$store.getters.token}}</time>
        <el-button type="text" class="button">操作按钮</el-button>
      </div>
    </div>
  </el-card>
</template>

<script>
export default {
  name: "Introduce",
  data() {
    return {
      currentDate: new Date(),
      currentUrl: 'https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png'
    };
  },
}
</script>

<style scoped>
.time {
  font-size: 13px;
  color: #999;
}

.bottom {
  margin-top: 13px;
  line-height: 12px;
}

.button {
  padding: 0;
  float: right;
}

.image {
  width: 100%;
  display: block;
}

.clearfix:before,
.clearfix:after {
  display: table;
  content: "";
}

.clearfix:after {
  clear: both
}
</style>
