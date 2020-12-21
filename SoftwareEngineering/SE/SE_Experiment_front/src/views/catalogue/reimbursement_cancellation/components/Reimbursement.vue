<template>
  <el-dialog title="报损与注销修改" :visible.sync="visible" width="40%">
    <el-form ref="reimbursement" :model="reimbursement" :rules="rules" label-width="100px">
      <el-form-item label="ISBN号" prop="isbn">
        <el-input v-model="reimbursement.isbn" :disabled="!isAdd" />
      </el-form-item>
      <el-form-item label="书名" prop="bookName">
        <el-input v-model="reimbursement.bookName" :disabled="!isAdd" />
      </el-form-item>
      <el-form-item label="报损原因" prop="reason">
        <el-input v-model="reimbursement.reason" />
      </el-form-item>
      <el-form-item label="书籍价格" prop="price">
        <el-input v-model.number="reimbursement.price" :disabled="!isAdd" />
      </el-form-item>
      <el-form-item label="审批状态" prop="state">
        <el-select v-model="reimbursement.state" placeholder="请选择状态">
          <el-option label="通过" value="通过" />
          <el-option label="未通过" value="未通过" />
        </el-select>
      </el-form-item>
      <el-form-item label="审批人" prop="checker">
        <el-input v-model="reimbursement.checker" />
      </el-form-item>
    </el-form>
    <div slot="footer">
      <el-button v-if="isAdd" type="primary" @click="addDamage">添加</el-button>
      <el-button v-if="!isAdd" type="primary" @click="updateDamage">提交更新</el-button>
      <el-button @click="resetForm('reimbursement')">重置</el-button>
    </div>
  </el-dialog>
</template>

<script>
import { addDamage, updateDamage } from '../../../../api/catalogue'

export default {
  name: 'Reimbursement',
  data() {
    return {
      visible: false,
      reimbursement: {
        isbn: '',
        bookName: '',
        reason: '',
        price: '',
        state: '',
        checker: ''
      },
      isAdd: false,
      rules: {
        isbn: [
          { required: true, message: '请输入ISBN', trigger: 'blur' },
          { min: 13, max: 13, message: '长度为13位', trigger: 'blur' }
        ],
        bookName: [
          { required: true, message: '请输入书名', trigger: 'blur' },
        ],
        reason: [
          { required: true, message: '请输入报损原因', trigger: 'blur' }
        ],
        price: [
          { required: true, message: '请输入价格(数字)' },
          { type: 'number'}
        ],
        state: [{
          required: true, message: '请选择审批状态', trigger: 'blur'
        }],
        checker: [
          { required: true, message: '请输入审批人姓名', trigger: 'change' }
        ]
      }
    }
  },
  watch: {
    'visible': function(value) {
      if (!value) {
        this.$refs['reimbursement'].resetFields()
        this.$parent.searchDamage()
      }
    }
  },
  methods: {
    resetForm(formName) {
      this.$refs[formName].resetFields()
    },
    addDamage() {
      this.$refs['reimbursement'].validate((valid) => {
        if (valid) {
          if (this.reimbursement.state === '通过') {
            this.reimbursement.state = true
          } else {
            this.reimbursement.state = false
          }
          addDamage({
            isbn: this.reimbursement.isbn,
            bookName: this.reimbursement.bookName,
            reason: this.reimbursement.reason,
            price: this.reimbursement.price,
            state: this.reimbursement.state,
            checker: this.reimbursement.checker
          }).then(response => {
            this.$message({
              type: 'success',
              message: response.msg
            })
            this.visible = false
          })
        }
      })
    },
    updateDamage() {
      this.$refs['reimbursement'].validate((valid) => {
        if (valid) {
          if (this.reimbursement.state === '通过') {
            this.reimbursement.state = true
          } else {
            this.reimbursement.state = false
          }
          updateDamage({
            isbn: this.reimbursement.isbn,
            bookName: this.reimbursement.bookName,
            reason: this.reimbursement.reason,
            price: this.reimbursement.price,
            state: this.reimbursement.state,
            checker: this.reimbursement.checker
          }).then(response => {
            this.$message({
              type: 'success',
              message: response.msg
            })
            this.visible = false
          })
        }
      })
    }
  }
}
</script>

<style scoped>

</style>
