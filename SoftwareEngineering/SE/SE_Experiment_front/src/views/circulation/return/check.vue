<template>
  <div>
    <el-dialog
      :visible.sync="modifyVisible"
      title="查看借书信息"
    >
      <el-form ref="form" :model="form" label-width="80px">
        <el-form-item label="书名">
          <el-input v-model="form.bookName" style="width: 30%" :disabled="true" />
        </el-form-item>
        <el-form-item label="isbn">
          <el-input v-model="form.isbn" style="width: 30%" :disabled="true" />
        </el-form-item>
        <el-form-item label="借书日期">
          <el-col :span="11">
            <el-date-picker v-model="form.borrowDate" :disabled="true" type="borrowDate" placeholder="选择日期" style="width: 100%;" />
          </el-col>
        </el-form-item>
        <el-form-item label="还书日期">
          <el-col :span="11">
            <el-date-picker v-model="form.returnDate" :disabled="true" type="returnDate" placeholder="选择日期" style="width: 100%;" />
          </el-col>
        </el-form-item>
        <el-form-item label="借阅期限">
          <el-input v-model="form.borrowPeriod" style="width: 10%" :disabled="true" /> 天
        </el-form-item>
      </el-form>
    </el-dialog>
  </div>
</template>

<script>

export default {
  name: 'Check',
  data() {
    return {
      modifyVisible: false,
      form: {
        bookName: '',
        isbn: '',
        borrowDate: '',
        returnDate: '',
        borrowPeriod: ''
      },
      src: ''
    }
  }
}
</script>

<style scoped>

</style>
